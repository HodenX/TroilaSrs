/*
The MIT License (MIT)

Copyright (c) 2013-2020 Winlin

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef SRS_UTEST_KERNEL_HPP
#define SRS_UTEST_KERNEL_HPP

/*
#include <srs_utest_kernel.hpp>
*/
#include <srs_utest.hpp>

#include <string>
#include <srs_kernel_file.hpp>
#include <srs_kernel_buffer.hpp>
#include <srs_protocol_stream.hpp>
#include <srs_kernel_ts.hpp>
#include <srs_kernel_stream.hpp>

class MockSrsFile
{
public:
    SrsBuffer* _buf;
    SrsSimpleStream _data;
public:
    MockSrsFile();
    virtual ~MockSrsFile();
public:
    virtual srs_error_t open(std::string file);
    virtual void close();
public:
    virtual srs_error_t write(void* data, size_t count, ssize_t* pnwrite);
    virtual srs_error_t read(void* data, size_t count, ssize_t* pnread);
    virtual srs_error_t lseek(off_t offset, int whence, off_t* seeked);
};

class MockSrsFileWriter : public SrsFileWriter
{
public:
    MockSrsFile* uf;
    srs_error_t err;
    // Error if exceed this offset.
    int error_offset;
    // Whether opened.
    bool opened;
public:
    MockSrsFileWriter();
    virtual ~MockSrsFileWriter();
public:
    virtual srs_error_t open(std::string file);
    virtual void close();
public:
    virtual bool is_open();
    virtual void seek2(int64_t offset);
    virtual int64_t tellg();
    virtual int64_t filesize();
    virtual char* data();
    virtual string str();
public:
    virtual srs_error_t write(void* buf, size_t count, ssize_t* pnwrite);
    virtual srs_error_t lseek(off_t offset, int whence, off_t* seeked);
// for mock
public:
    void mock_reset_offset();
};

class MockSrsFileReader : public SrsFileReader
{
public:
    MockSrsFile* uf;
    bool opened;
    // Could seek.
    bool seekable;
public:
    MockSrsFileReader();
    MockSrsFileReader(const char* data, int nb_data);
    virtual ~MockSrsFileReader();
public:
    virtual srs_error_t open(std::string file);
    virtual void close();
public:
    virtual bool is_open();
    virtual int64_t tellg();
    virtual void skip(int64_t size);
    virtual int64_t seek2(int64_t offset);
    virtual int64_t filesize();
public:
    virtual srs_error_t read(void* buf, size_t count, ssize_t* pnread);
    virtual srs_error_t lseek(off_t offset, int whence, off_t* seeked);
// for mock
public:
    // append data to current offset, modify the offset and size.
    void mock_append_data(const char* _data, int _size);
    void mock_reset_offset();
};

class MockBufferReader: public ISrsReader
{
private:
    std::string str;
public:
    MockBufferReader(const char* data);
    virtual ~MockBufferReader();
public:
    virtual srs_error_t read(void* buf, size_t size, ssize_t* nread);
};

class MockSrsCodec : public ISrsCodec
{
public:
    MockSrsCodec();
    virtual ~MockSrsCodec();
public:
    virtual int nb_bytes();
    virtual srs_error_t encode(SrsBuffer* buf);
    virtual srs_error_t decode(SrsBuffer* buf);
};

class MockTsHandler : public ISrsTsHandler
{
public:
    SrsTsMessage* msg;
public:
    MockTsHandler();
    virtual ~MockTsHandler();
public:
    virtual srs_error_t on_ts_message(SrsTsMessage* m);
};

#endif
