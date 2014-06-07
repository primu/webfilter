#include "stdafx.h"
#include "PasswordHash.h"


PasswordHash::PasswordHash(void)
{
}

String^ PasswordHash::CreateHash(String^ password)
{
	RNGCryptoServiceProvider^ r = gcnew RNGCryptoServiceProvider();
	array<Byte>^ salt = gcnew array<Byte>(SALT_BYTE_SIZE);
	r->GetBytes(salt);
	array<Byte>^ hash = PBKDF2(password,salt,PKDF2_ITERATIONS,HASH_BYTE_SIZE);
	return PKDF2_ITERATIONS+":"+Convert::ToBase64String(salt)+":"+Convert::ToBase64String(hash);
};

bool PasswordHash::ValidatePassword(String^ password, String^ correctHash)
{
	Char d = ':';

	array<String^>^ split = correctHash->Split(d);
	int iterations = Int32::Parse(split[ITERATION_INDEX]);
	array<Byte>^ salt = Convert::FromBase64String(split[SALT_INDEX]);
	array<Byte>^ hash = Convert::FromBase64String(split[PBKDF2_INDEX]);


	array<Byte>^ test = PBKDF2(password,salt,iterations,hash->Length);
	return SlowEquals(hash, test);
}

bool PasswordHash::SlowEquals(array<Byte>^ a, array<Byte>^ b)
{
	UInt32 diff = (UInt32)a->Length ^ (UInt32)b->Length;
	for(int i =0; i<a->Length && i <b->Length;i++)
	{
		diff |= (UInt32)(a[i]^b[i]);
	}
	return diff==0?true:false;
}

array<Byte>^ PasswordHash::PBKDF2(String^ password, array<Byte>^ salt, int iterations, int outputBytes)
{
	Rfc2898DeriveBytes^ pbkdf2 = gcnew Rfc2898DeriveBytes(password,salt);
	pbkdf2->IterationCount=iterations;
	return pbkdf2->GetBytes(outputBytes);
}