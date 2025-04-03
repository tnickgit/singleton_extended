//db.h
#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include <new>
#include <ctime> 

using namespace std;

class Database {
private:
	string db;
	string username;
	string password;
	string connected = "false";
	static Database* instance;
	time_t last_activity;
	static const int TIMEOUT{ 5 };

	Database(string DB, string UN, string PW) :
		db{ DB }, username{ UN }, password{ PW }, last_activity{ std::time(nullptr) }
	{}

	~Database()
	{
		if (isConnected())
		{
			cout << "Disconnect connection" << endl;
			connected = "false";
		}
	}

public:

	Database(Database& src) {
		throw std::runtime_error("Cannot have copy constructor");
	}

	Database& operator=(Database& src) {
		throw std::runtime_error("Cannot have a copy assignment constructor");
	}

	Database(Database&& src) {
		throw std::runtime_error("Cannot have a move constructor");
	}

	Database& operator=(Database&& src) {
		throw std::runtime_error("Cannot have a move assignment operator");
	}

	//"getInstance" that creates and returns the instance of the database. 
	// If called first time it sets the username and password. 
	// However, subsequent time, it matches the database name, 
	// username and password and returns the previous instance 
	// if matched else it throws std::runtime_error("invalid database name, username or password"). 
	// We are using Singleton Design Pattern that creates only one instance of the databse. The instance is still created by the constructor.
	//ToDo
	static Database* getInstance(string DB, string UN, string PW)
	{
		if (!instance)
		{
			instance = new Database(DB, UN, PW);
		}
		else if (instance->db != DB || instance->username != UN || instance->password != PW) {
			throw std::runtime_error("invalid database name, username or password");
		}

		return instance;
	}

	//"connect" that sets "connected" to true (return void)
	void connect();

	//"connect" that sets "connected" to true (return void)
	void disconnect();

	// retrun status of connected true/false (return bool)
	bool isConnected();

	//overload the new operator that allocates memory using malloc 
	// of given size and returns pointer of type void and prints " overloaded new " 
	// (cout is okay in this case). std::cout << "overloaded new ";
	//If the memory allocation fails it should throw std::bad_alloc()
	void* operator new(size_t size);
	
	//overload the delete operator that deallocates memory and prints 
	// "overloaded delete " (cout is okay in this). std::cout << "overloaded delete ";
	void operator delete(void* ptr);

	//set_username and get_username for username
	string get_username() const;
	void set_username(const string newUN);

	//set_password and get_password for password.
	string get_password() const;
	void set_password(const string newPW);

	//The static "resetInstance" as defined below.
	static void resetInstance();

	// Checks if the connection has been inactive for longer than TIMEOUT seconds
	// Returns true if the timeout threshold has been exceeded, false otherwise
	bool isTimeout();

	// Updates the last_activity timestamp to the current time
	// Should be called whenever there is interaction with the database to reset the timeout
	void refreshConnection();

	//Implement a timeout of 5 seconds. Connection to be disconnected after inactivity of 5 seconds.
	void inactivityDisconnect();

};