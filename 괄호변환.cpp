



// test.cpp : �� ���Ͽ��� 'main' �Լ��� ���Ե˴ϴ�. �ű⼭ ���α׷� ������ ���۵ǰ� ����˴ϴ�.
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
    //�Է�
    
    string answer = "";
    string u = "";
    string v = "";
    string strTemp = "";

    //1. �Է��� �� ���ڿ��� ���, �� ���ڿ��� ��ȯ�մϴ�. 
    if (p.empty())
        return "";

    //2. ���ڿ� w�� �� "�������� ��ȣ ���ڿ�" u, v�� �и��մϴ�. 
    //u�� "�������� ��ȣ ���ڿ�"�� �� �̻� �и��� �� ����� �ϸ�
    //v�� �� ���ڿ��� �� �� �ֽ��ϴ�.
    Split(p, u, v);

    //3. ���ڿ� u�� "�ùٸ� ��ȣ ���ڿ�" �̶�� ���ڿ� v�� ���� 1�ܰ���� �ٽ� �����մϴ�. 
    //  3-1. ������ ��� ���ڿ��� u�� �̾� ���� �� ��ȯ�մϴ�. 
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
    //4. ���ڿ� u�� "�ùٸ� ��ȣ ���ڿ�"�� �ƴ϶�� �Ʒ� ������ �����մϴ�. 
    //  4-1. �� ���ڿ��� ù ��° ���ڷ� '('�� ���Դϴ�. 
    //  4-2. ���ڿ� v�� ���� 1�ܰ���� ��������� ������ ��� ���ڿ��� �̾� ���Դϴ�. 
    //  4-3. ')'�� �ٽ� ���Դϴ�. 
    //  4-4. u�� ù ��°�� ������ ���ڸ� �����ϰ�, ������ ���ڿ��� ��ȣ ������ ����� �ڿ� ���Դϴ�. 
    //  4-5. ������ ���ڿ��� ��ȯ�մϴ�.

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