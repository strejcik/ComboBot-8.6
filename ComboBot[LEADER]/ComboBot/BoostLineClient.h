#include "pch.h"
#pragma once

#ifndef BoostLineClient_H_GUARD       // include guard
#define BoostLineClient_H_GUARD

using boost::asio::ip::tcp;
typedef std::deque<std::string> chat_message_queue;
class BoostLineClient
{
public:
	BoostLineClient(boost::asio::io_service& io_service, tcp::resolver::iterator endpoint_iterator)
		: io_service_(io_service), socket_(io_service)
	{
		tcp::endpoint endpoint = *endpoint_iterator;
		//socket_.non_blocking(true);
		socket_.async_connect(
			endpoint,
			boost::bind(&BoostLineClient::handle_connect, this, boost::asio::placeholders::error, ++endpoint_iterator));
	}

	void write(std::string message)
	{
		io_service_.post(boost::bind(&BoostLineClient::do_write, this, message));
	}


	void close()
	{
		io_service_.post(boost::bind(&BoostLineClient::do_close, this));
	}

	void invokeRead()
	{
		//async_read(socket_,
		//	boost::asio::buffer(read_msg_.data(), read_msg_.length()),
		//	boost::bind(&line_client::handle_read_body, this,
		//		boost::asio::placeholders::error));
		socket_.async_read_some(boost::asio::buffer(read_msg_.data(), read_msg_.length()), boost::bind(&BoostLineClient::handle_read_body, this,
			boost::asio::placeholders::error));
	}

	bool isConnected() {
		return socket_.is_open();
	}
	std::string reply, r, msg;
	boost::asio::streambuf buffer;
	tcp::socket socket_;

private:

	std::string bufferToString(char* buffer, int bufflen)
	{
		std::string ret(buffer, bufflen);

		return ret;
	}
	void handle_connect(const boost::system::error_code& error, tcp::resolver::iterator endpoint_iterator)
	{
		using boost::asio::async_read_until;
		using boost::asio::buffer;




		if (error) {
			std::cerr << "connection error: " << error << std::endl;

			if (endpoint_iterator == tcp::resolver::iterator())
			{
				std::cerr << "not connecting any longer" << std::endl;
				return;
			}

			socket_.close();

			tcp::endpoint endpoint = *endpoint_iterator;

			/*socket_.async_connect(
				endpoint,
				boost::bind(&line_client::handle_connect, this, boost::asio::placeholders::error, ++endpoint_iterator));*/

			return;
		}



		//if (!error) {
		//	socket_.async_read_some(boost::asio::buffer(read_msg_.data(), read_msg_.length()), boost::bind(&line_client::handle_read_body, this,
		//		boost::asio::placeholders::error));
		//}

	}


	void handle_read_header(const boost::system::error_code& error)
	{


		if (!error)
		{
			//boost::asio::async_read(socket_,
			//	boost::asio::buffer(read_msg_.data(), read_msg_.length()),
			//	boost::bind(&line_client::handle_read_body, this,
			//		boost::asio::placeholders::error));
			socket_.async_read_some(boost::asio::buffer(read_msg_.data(), read_msg_.length()), boost::bind(&BoostLineClient::handle_read_body, this,
				boost::asio::placeholders::error));
		}
		else
		{
			do_close();
		}
	}

	void handle_read_body(const boost::system::error_code& error)
	{
		if (!error)
		{
			/*std::string s = read_msg_.data();
			s.assign(read_msg_.data(), read_msg_.data() + read_msg_.length());
			std::cout << s.c_str();*/
			//if (!read_msg_.length() == 0)
			//{
			//	std::cout << read_msg_.data();
			//	std::cout << "\n";
			//}
			//
			std::cout << read_msg_.data();
			std::cout << "\n";

			//return;
			if (read_msg_.length() > 0) {
				read_msg_.setDataToEmpty();
				return;
			}
			//boost::asio::async_read(socket_,
			//	boost::asio::buffer(read_msg_.data(), read_msg_.length()),
			//	boost::bind(&line_client::handle_read_header, this,
			//		boost::asio::placeholders::error));

			socket_.async_read_some(boost::asio::buffer(read_msg_.data(), read_msg_.length()), boost::bind(&BoostLineClient::handle_read_header, this,
				boost::asio::placeholders::error));

		}
		else
		{
			do_close();
		}
	}


	void report_error(boost::system::error_code ec) {
		std::cout << "Error: " << ec.message() << "\n";
	}



	void do_write(std::string message)
	{
		using boost::asio::async_write;
		using boost::asio::buffer;

		bool write_in_progress = !write_msgs_.empty();

		write_msgs_.push_back(message);

		if (write_in_progress) {
			return;
		}

		async_write(
			socket_,
			buffer(write_msgs_.front().data(), write_msgs_.front().length()),
			boost::bind(&BoostLineClient::handle_write, this, boost::asio::placeholders::error));
	}

	void handle_write(const boost::system::error_code& error)
	{
		using boost::asio::async_write;
		using boost::asio::buffer;

		if (error) {
			do_close();
			return;
		}

		write_msgs_.pop_front();

		if (!write_msgs_.empty())
		{
			async_write(
				socket_,
				buffer(write_msgs_.front().data(), write_msgs_.front().length()),
				boost::bind(&BoostLineClient::handle_write, this, boost::asio::placeholders::error));
		}
	}

	void do_close() {
		std::cerr << "closing socket" << std::endl;
		socket_.close();
	}



private:
	boost::asio::io_service& io_service_;
	boost::asio::streambuf buffer_;
	chat_message_queue write_msgs_;
	chat_message_queue read_msgs_;
	Message read_msg_;
	bool read_in_progress = !read_msg_.length() == 0;
};

#endif