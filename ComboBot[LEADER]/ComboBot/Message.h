
#include "pch.h"
#pragma once

#ifndef Message_H_GUARD       // include guard
#define Message_H_GUARD  



class Message
{
public:
	enum { header_length = 10 };
	enum { max_body_length = 10 };

	Message()
		: body_length_(0)
	{
	}

	const char* data() const
	{
		return data_;
	}

	char* data()
	{
		return data_;
	}

	void setDataToEmpty()
	{
		memset(data_, 0, sizeof data_);
	}

	size_t length() const
	{
		return header_length + body_length_;
	}

	const char* body() const
	{
		return data_ + header_length;
	}

	char* body()
	{
		return data_ + header_length;
	}

	size_t body_length() const
	{
		return body_length_;
	}

	void body_length(size_t new_length)
	{
		body_length_ = new_length;
		if (body_length_ > max_body_length)
			body_length_ = max_body_length;
	}

private:
	char data_[header_length + max_body_length];
	size_t body_length_;
};

#endif