#include <string> // 使用处：第 15 行的 string
#include <unordered_map> // 使用处：第 15 行的 unordered_map
#include <iostream> // 使用处：第 22 行的 cout
using namespace std;
int main()
{	
	//Node* head=creat_node(0);
	//for (int i = 1; i < 10; i++) {
	//	tail_insert(head, creat_node(i));
	//}
	//Printlist(head);
	///*reverse_list(head);*/
	//Node* h=reverse_node(head);
	//Printlist(h);
	unordered_map<string, int> hash;
	unordered_map<string, int> map;
	unordered_map<string, int>::iterator t;
	hash.insert({ "zuo", 31 });
	hash.insert({ "yao", 2 });
	hash.insert({ "laozhang", 46 });
	t=hash.find("yao");
	cout << hash["yao"] << endl;
	if (t != hash.end())
		cout << "true" << endl;
	else
		cout << "false" << endl;
	return 0;

}