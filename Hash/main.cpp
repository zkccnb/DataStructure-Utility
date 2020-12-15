#include"ChainDic.hpp"
#include"HashTable.hpp"
using namespace std;
void test_ChainDic()
{
	try
	{
		int key[] = { 4,3,5,0,2,1 };
		float value[] = { 1.1f,1.2f,1.3f,1.4f,1.5f,1.6f };
		Pair<int, float>* pair[6];
		for (int i = 0; i < 6; i++) pair[i] = new Pair<int, float>(key[i], value[i]);
		Dictionary<int, float>* dic;//构造函数是空的时候一定不能加括号,编译器会以为你在声明函数！
		ChainDictionary<int, float> chainDic;//必须要重写抽象类的所有函数子类才不被认为是抽象类！
		dic = &chainDic;
		for (int i = 0; i < 6; i++) dic->insert(*pair[i]);
		dic->erase(1);
		//dic->erase(6);
		//dic->erase(4);
		std::cout << dic->find(4) << std::endl;
		std::cout << dic->find(3) << std::endl;
		std::cout << dic->find(10) << std::endl;
		std::cout << chainDic << std::endl;
	}
	catch (const char* str)
	{
		std::cout << str << std::endl;
	}
}
void test_hash_int()
{
	try
	{
		int key[] = { 4,3,5,0,2,1 };
		float value[] = { 1.1f,1.2f,1.3f,1.4f,1.5f,1.6f };
		Pair<int, float>* pair[6];
		for (int i = 0; i < 6; i++) pair[i] = new Pair<int, float>(key[i], value[i]);
		Dictionary<int, float>* dic;
		Hash<int, float> hash(6);
		dic = &hash;
		for (int i = 0; i < 6; i++) dic->insert(*pair[i]);
		std::cout << dic->find(4) << std::endl;
		dic->erase(2);
		std::cout << hash << std::endl;
	}
	catch (const char* str)
	{
		std::cout << str << std::endl;
	}
}
void test_hash_string()
{
	try
	{
		string key[] = { "zkcc1","zkcc2","zkcc3","zkcc4","zkcc5","zkcc6" };
		int value[] = { 1,2,3,4,5,6 };
		Pair<string, int>* pair[6];
		for (int i = 0; i < 6; i++) pair[i] = new Pair<string, int>(key[i], value[i]);
		Dictionary<string, int>* dic;
		Hash<string, int> hash(6);
		Dictionary<string, int>* dic1;
		dic = &hash;
		for (int i = 0; i < 6; i++) dic->insert(*pair[i]);
		//std::cout << dic->find("zkcc1") << std::endl;
		//dic->erase("zkcc1");
		std::cout <<"dic:"<< hash << std::endl;
		//关于拷贝构造还得详看C++P第13章
		dic1 = new Hash<string, int>(hash);//当用某对象给另一对象初始化时会调用拷贝构造
		//dic1 = &hash;//这样不会调用拷贝构造
		//dic1 = dic;//这样不会调用拷贝构造
		std::cout << "dic1:" << hash << std::endl;
		std::cout << "dic size:" << dic->size() << std::endl;
		std::cout << "dic1 size:" << dic1->size() << std::endl;
	}
	catch (const char* str)
	{
		std::cout << str << std::endl;
	}
}
int main()
{
	//test_ChainDic();
	//test_hash_int();
	test_hash_string();
	return 0;
}

