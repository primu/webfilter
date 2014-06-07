#pragma once
using namespace System;
using namespace System::Security::Cryptography;

ref class PasswordHash
{
public:
	static const int SALT_BYTE_SIZE = 24;
	static const int HASH_BYTE_SIZE = 24;
	static const int PKDF2_ITERATIONS = 1000;

	static const int ITERATION_INDEX = 0;
	static const int SALT_INDEX = 1;
	static const int PBKDF2_INDEX = 2;
	PasswordHash(void);

	static String^ CreateHash(String^ password);
	static bool ValidatePassword(String^ password, String^ correctHash);
	static bool SlowEquals(array<Byte>^ a, array<Byte>^ b);
private:
	static array<Byte>^ PBKDF2(String^ password, array<Byte>^ salt, int iterations, int outputBytes);
};

