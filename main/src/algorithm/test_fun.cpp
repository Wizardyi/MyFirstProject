#include"test_fun.h"


void TestFun::dfs(int iPush,int iPop,std::string& a,std::string& b,stack<char>& build,vector<char>& operate)
{
	int length = a.length();
	if(iPush == length && iPop == length){
		for(int i = 0; i < (int)operate.size();i++)
		{
			cout << operate[i] << "";
		}
		cout << endl;
	}

	//入栈
	if(iPush + 1 <= length)
	{
		build.push(a[iPush]);
		operate.push_back('i');
		dfs(iPush + 1,iPop,a,b,build,operate);
		build.pop();
		operate.pop_back();
	}

	//出栈
	if(iPop + 1 <= iPush && iPop + 1 <= length && build.top() == b[iPop])
	{
		char tc = build.top();
		build.pop();
		operate.push_back('o');
		dfs(iPush,iPop + 1,a,b,build,operate);
		build.push(tc);
		operate.pop_back();
	}



}

