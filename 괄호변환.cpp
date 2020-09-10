



// test.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int Check(string u)
{
    int nOp = 0;
    int nCl = 0;
    int nULen = u.length();

    for (int i = 0; i < nULen; i++)
    {
        if (u[i] == '(')
            nOp++;
        else
            nCl++;

        if (nOp < nCl)
            return false;
    }

    return true;
}
int Split(/*in*/string w, /*out*/string &u, /*out*/string &v)
{
    int nOp = 0;
    int nCl = 0;

    int nWLen = w.length();

    for (int i = 0; i < nWLen; i++)
    {
        if (w[i] == '(')
            nOp++;
        else
            nCl++;

        //u[i] = w[i];
        u.push_back(w.at(i));

        if (nOp == nCl)
        {
            if (i < nWLen - 1)
                v = w.substr(i + 1, i + 1 - nWLen);
            //v.copy(w.c_str(), i+1-nWLen, i+1);

            return true;
        }
    }

    return true;
}

string solution(string p) 
{
    //입력
    
    string answer = "";
    string u = "";
    string v = "";
    string strTemp = "";

    //1. 입력이 빈 문자열인 경우, 빈 문자열을 반환합니다. 
    if (p.empty())
        return "";

    //2. 문자열 w를 두 "균형잡힌 괄호 문자열" u, v로 분리합니다. 
    //u는 "균형잡힌 괄호 문자열"로 더 이상 분리할 수 없어야 하며
    //v는 빈 문자열이 될 수 있습니다.
    Split(p, u, v);

    //3. 문자열 u가 "올바른 괄호 문자열" 이라면 문자열 v에 대해 1단계부터 다시 수행합니다. 
    //  3-1. 수행한 결과 문자열을 u에 이어 붙인 후 반환합니다. 
    if (Check(u))
    {
        answer = u + solution(v);
        return answer;
    }
    else
    {
        strTemp = '(' + solution(v) + ')';
        //u[0] = "";
        u.replace(0, 1, "");
        u.pop_back();
        for (int i = 0; i < u.length(); i++)
        {
            if (u[i] == '(')
                strTemp += ')';
            else
                strTemp += '(';
        }

        return strTemp;
    }
    //4. 문자열 u가 "올바른 괄호 문자열"이 아니라면 아래 과정을 수행합니다. 
    //  4-1. 빈 문자열에 첫 번째 문자로 '('를 붙입니다. 
    //  4-2. 문자열 v에 대해 1단계부터 재귀적으로 수행한 결과 문자열을 이어 붙입니다. 
    //  4-3. ')'를 다시 붙입니다. 
    //  4-4. u의 첫 번째와 마지막 문자를 제거하고, 나머지 문자열의 괄호 방향을 뒤집어서 뒤에 붙입니다. 
    //  4-5. 생성된 문자열을 반환합니다.

    return answer;
}

int main()
{
    string p = "()))((()";//()))((()//(()())()
    string answer = "";
    answer = solution(p);

    cout << "answer : [" <<answer << "]\n   End\n" << endl;

    return true;
}