/**
 * Tencent is pleased to support the open source community by making Tars available.
 *
 * Copyright (C) 2016THL A29 Limited, a Tencent company. All rights reserved.
 *
 * Licensed under the BSD 3-Clause License (the "License"); you may not use this file except
 * in compliance with the License. You may obtain a copy of the License at
 *
 * https://opensource.org/licenses/BSD-3-Clause
 *
 * Unless required by applicable law or agreed to in writing, software distributed
 * under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, either express or implied. See the License for the
 * specific language governing permissions and limitations under the License.
 */
#ifndef _TARS_PROTOCOL_H_
#define _TARS_PROTOCOL_H_

#include <string>
#include <vector>
#include <tup/Tars.h>
#include <tup/RequestF.h>
#include "protocol.h"

using namespace std;
using namespace tars;

namespace bm
{
    struct Field
    {
        int tag_;
        bool require_;
        string type_;
    };

    class tarsProtocol : public Protocol
    {
        DECLARE_DYNCREATE(tarsProtocol)
    public:
        tarsProtocol() {}
        virtual ~tarsProtocol() {}
        /**
         * @brief  协议初始化函数
         *
         * @param argc 参数个数
         * @param argv 参数内容
         *
         * @return 0成功, 其他失败
         */
        virtual int initialize(int argc, char** argv);

        /**
         * @brief  协议是否支持有序的
         *
         * @return true: 支持, false: 不支持
         */
        virtual int isSupportSeq() { return true; }

        /**
         * @brief  判断收包是否完整
         *
         * @param buf  数据包指针
         * @param len  网络数据包长度
         *
         * @return int =0报文不完整; >0:实际报文长度; <0:出错
         */
        virtual int input(const char *buf, size_t len);

        /**
         * @brief  TARS服务协议打包
         *
         * @param buf  数据包指针
         * @param len  数据包长度
         * @param uniqId  全局唯一ID
         *
         * @return 0成功, 其他失败
         */
        virtual int encode(char *buf, int& len, int& uniqId);
        virtual int decode(const char *buf, int len, int& uniqId);

        /**
         * @brief  TARS协议编解码
         *
         * @param os/is 缓存区
         * @param type  类型
         * @param val   Val值
         * @param tag   编号
         * @param usigned  数据类型
         *
         * @return 0成功, 其他失败
         */
        int encode(TarsOutputStream<BufferWriter> &os, const string& type, const string& val, int tag, bool usigned = false);
        string decode(TarsInputStream<BufferReader> &is, const string& type, int tag, bool require, bool usigned  = false);

    private:
        /**
         * @brief  获得类型
         *
         * @param type  业务数据实例
         *
         * @return  string
         */
        string getType(const string& type);

        /**
         * @brief  解析成员变量
         *
         * @param type 数据类型
         * @param tag  数据编号
         * @param require 是否必须
         *
         * @return Field结构
         */
        Field getField(const string& type, int tag, bool require);

        /**
         * @brief  解析列表成员
         *
         * @param val 配置string变量
         *
         * @return vector<string>
         */
        vector<string> getArray(const string& val);

        /**
         * @brief  获得map的key/value
         *
         * @param type  业务数据实例
         *
         * @return  string
         */
        string getMapKey(const string& type);
        string getMapValue(const string& type);

        /**
         * @brief  生成取随机内容
         *
         * @param req 业务数据实例
         *
         * @return 0成功, 其他失败
         */
        long genRandomValue(const string& rmin, const string& rmax);
        string genRandomValue(const string& v, bool isIntegal = true);

        /**
         * @brief  解析测试用例文件
         *
         * @param sFileName 测试用例文件
         *
         * @return 0成功, 其他失败
         */
         int parseCaseFile(const string& sFileName);
    private:
        int             _timeOut;
        string          _servant;
        string          _function;
        vector<string>  _paraVals;
        vector<string>  _paraList;
    };
};
#endif
