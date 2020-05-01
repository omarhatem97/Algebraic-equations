#include<iostream>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <vector>
#include <utility>
#include <sstream>
#include <set>
using namespace std;

/*  global variables used in the programme */

float determ[100][100]; //determinate  
vector<string>components; // components before and after the equal sign 
vector < pair<string, string>> lhsp;  //left hand side as a pair
string rhs;  // rhs (el 7ad el motlak)

/*----------------------------------------------*/


/* helping functions */

void print(vector < pair<string, string>>v)
{
	cout << "the vector : " << endl;
	for (auto c : v)
	{
		cout << c.first << "   " << c.second << endl;
	}
}
void print(vector<string> v)
{
	for (int i = 0; i < v.size(); i++)
	{
		cout << v[i] << endl;
	}
}
void print_D(int row, int col)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			cout << determ[i][j] << "\t";
		}
		cout << endl;
	}
}

string to_str(float f)
{
	string str;
	ostringstream ss;
	ss << f;
	str = ss.str();
	return str;
}

string to_str(string s)
{
	string res;
	for (int i = 0; i < s.size(); i++)
	{
		if ((s[i] >= '0' && s[i] <= '9') || s[i] == '-' ) continue;
		else
		{
			res += s.substr(i);
			break;
		}
	}
	return res;
}

bool is_num(char c)
{
	if ((c >= '0' && c <= '9') || c == '.') return true;
	return false;
}

bool is_num(string s)
{
	for (int i = 0; i < s.size(); i++)
	{
		if ((s[i] >= '0' && s[i] <= '9') || s[i] == '.') continue;
		else return false;
	}
	return true;
}

bool is_float(string s)
{
	float temp = atof(s.c_str());
	int x = temp;
	if (temp - x >= 0.0000001) return true;
	else return false;
}

bool compare(std::pair<string, string>&ls, std::pair<string, string>&rs)
{
	int index1 = 0 , index2 = 0;

	for (int i = 0; i < ls.first.size(); i++)
	{
		if (!is_num(ls.first[i]) && ls.first[i] != '+' && ls.first[i] != '-' &&ls.first[i] != '_')
		{
			index1 = i;
			break;
		}
	}
	for (int i = 0; i < rs.first.size(); i++)
	{
		if (!is_num(rs.first[i]) && rs.first[i] != '+' && rs.first[i] != '-' && rs.first[i] != '_')
		{
			index2 = i;
			break;
		}
	}
	return ls.first.substr(index1) < rs.first.substr(index2);
}
bool sortBySecond(std::pair<string, string>&ls, std::pair<string, string>&rs)
{
	return atof(ls.second.c_str()) < atof(rs.second.c_str());
}
bool sort_set(string &lhs, string&rhs)
{
	string s1, s2;
	for (int  i = 0; i < lhs.size(); i++)
	{
		if (is_num(lhs[i]))
		{
			s1 += lhs.substr(i);
			break;
		}
	}
	for (int i = 0; i < rhs.size(); i++)
	{
		if (is_num(rhs[i]))
		{
			s2 += rhs.substr(i);
			break;
		}
	}
	return atof(s1.c_str()) < atof(s2.c_str());
}


string getvar(string s) // getvar is used by sortRank and computer duplicates
{
	for (int j = 0; j < s.size(); j++)
	{
		if ((s[j] >= '0' && s[j] <= '9') || s[j] == '+' || s[j] == '-'||s[j] == '.') continue;
		else
		{
			return s.substr(j);
		}
	}
}
vector<pair<string, string>> compute_duplicates(vector<pair<string, string>>&v)
{
	vector<pair<string, string>>res;
	int start = 0, end = 0; bool flag = 1; float sum = 1;

	if ((v[0].first[0] >= '0' && v[0].first[0] <= '9')
		|| (v[0].first[0] == '+' && (v[0].first[1] >= '0' && v[0].first[1] <= '9')) 
		|| (v[0].first[0] == '-' && (v[0].first[1] >= '0' && v[0].first[1] <= '9'))) // to avoid that (x1) become 0x1 instead of 1x1
	{
		sum = atof(v[0].first.c_str());
	}
	else sum = 1;

	for (int i = 0; i < v.size() - 1; i++)
	{
		if (getvar(v[start].first) + v[start].second == getvar(v[i + 1].first) + v[i + 1].second)
		{
			if ((v[i + 1].first[0] >= '0' && v[i + 1].first[0] <= '9') 
				|| v[i + 1].first[0] == '+' && (v[i+1].first[1] >= '0' && v[i+1].first[1] <= '9')
				|| v[i + 1].first[0] == '-' && (v[i + 1].first[1] >= '0' && v[i + 1].first[1] <= '9'))
			{ 
				sum += atof(v[i + 1].first.c_str());
			}	
			else if (v[i + 1].first[0] == '-' && ((v[i + 1].first[1] >= 'a' && v[i + 1].first[1] <= 'z') || (v[i + 1].first[1] >= 'A' && v[i + 1].first[1] <= 'Z')))
			{
				sum -=1;
			}
			else sum += 1;
			end++;
			flag = 1;
		}
		else
		{
			res.push_back(make_pair(to_str(sum) + getvar(v[start].first), v[start].second));
			if ((v[i + 1].first[0] >= '0' && v[i + 1].first[0] <= '9')
				|| v[i + 1].first[0] == '+' && (v[i + 1].first[1] >= '0' && v[i + 1].first[1] <= '9')
				|| v[i + 1].first[0] == '-' && (v[i + 1].first[1] >= '0' && v[i + 1].first[1] <= '9'))
			{
				sum = atof(v[i + 1].first.c_str());
				//end++;
			}
			else if (v[i + 1].first[0] == '-' && ((v[i + 1].first[1] >= 'a' && v[i + 1].first[1] <= 'z') || (v[i + 1].first[1] >= 'A' && v[i + 1].first[1] <= 'Z')))
			{
				sum = -1;
			}
			else sum = 1;
			flag = 0;
			end++;
			start = end;
		}
	}
	if (flag) res.push_back(make_pair(to_str(sum) + getvar(v[start].first), v[start].second));
	else if (start == end)
	{
		res.push_back(make_pair(to_str(sum) + getvar(v[start].first), v[end].second));
	}
	
	return res;
}

void compute_rhs(vector<string>& v)
{
	int res = 0;
	for (int i = 0; i < v.size(); i++)
	{
		res += atof(v[i].c_str());
	}
	rhs = to_str(res);
}

void print_equ_i(vector<pair<string,string> > v)
{
	//if (v[0].first[0] == '0') cout << v[0].first.substr(1) << v[0].second;
	for (int i = 0; i < v.size(); i++)
	{
		if (is_float(v[0].first))
		{
			if (v[i].first[0] != '-')
			{
				if (i == 0) cout << v[i].first << v[i].second;
				else cout << '+' << v[i].first << v[i].second;
			}
			else
			{
				cout << v[i].first << v[i].second;
			}
		}
		else
		{
			if (v[i].first[0] != '-' && v[i].first[0] != '0' && v[i].first[0] != '1')
			{
				if (i == 0) cout << v[i].first << v[i].second;
				else cout << '+' << v[i].first << v[i].second;
			}
			else if (v[i].first[0] == '0' || v[i].first[1] == '0')
			{
				continue;
			}
			else if (v[i].first[0] == '1')
			{
				if (i == 0) cout << v[i].first.substr(1) << v[i].second;
				else cout << '+' <<v[i].first.substr(1) << v[i].second;
			}
			else if (v[i].first[0] == '-' &&v[i].first[1] == '1')
			{
				std::cout << '-' << v[i].first.substr(2) << v[i].second;
			}
			else if (v[i].first[0] == '-' &&v[i].first[1] != '1')
			{
				cout << '-' << v[i].first.substr(1) << v[i].second;
			}
			else
			{
				if (i == 0) cout << v[i].first << v[i].second;
				else std::cout << '+' << v[i].first << v[i].second;
			}
		}

		
	}
	cout << "=";
	cout << rhs << endl;
}

bool found(string s)
{
	for (int i = 0; i < lhsp.size(); i++)
	{
		if (lhsp[i].second == s) return true;
	}
	return false;
}

vector<pair<string, string>> sortAlpha(vector<pair<string, string>> &v)
{
	vector<pair<string,string>> res;
	for (auto elemnt : v)
	{
		string s = elemnt.first;
		string num;
		for (int i = 0; i < s.size(); i++)
		{
			if (s[i] >= '0' && s[i] <= '9' || s[i] == '+' || s[i]== '-') num += s[i];
			else
			{
				res.push_back( make_pair(num, s.substr(i)) );
				break;
			}
		}
	}
	sort(res.begin(), res.end(),compare);
	return res;
}

 void sortRank(vector<pair<string, string>>& v)
{
	int start = 0; int end = 1; bool flag = 1;
	for (int i = 0; i < v.size() - 1; i++)
	{
		if (getvar(v[start].first) == getvar(v[i + 1].first))
		{
			end++;
			flag = 1;
		}
		else
		{
			sort(v.begin() + start, v.begin() + end, sortBySecond);
			flag = 0;
			end++;
			start = end-1;
		}
	}
	if (flag) sort(v.begin() + start, v.begin() + end, sortBySecond);
}


/*----------------------------------------------------*/

/*  functions declarations */

void slice(vector<string>equations);  // slice the equation into
int num_vars(vector<string> components);
vector<pair<string, string>> equation_i(string eq); // print equation i in the proper form
vector<string> coloumn(string s, vector<string>);
void add(int a, int b , vector<string>equations);
void subtract(int a, int b, vector<string>equations);
void substitute(string var, int a, int b, vector<string> equations);
void d(vector<string> equations);
void d_x(string s, vector<string> equations);
float D_value(float a[100][100], int n);
void solve(vector<string>equations);

/*------------------------------------*/


int main()
{
	int n;
	string s, operation;
	vector<string>equations;
	cin >> n;
	cin >> ws;
	for (int i = 0; i < n; i++) // taking equations
	{
		getline(cin, s);
		equations.push_back(s);
	}

	// getting operations
	getline(cin, operation);
	while (operation != "quit")
	{
		int idx = operation.find(" ");
		if (operation == "num_vars") // num_vars
		{
			slice(equations);
			cout << num_vars(components) << endl;
		}
		else if (operation[0] == 'e')  // equation_i
		{
			int index = 0;
			for (int i = 0; i < operation.size(); i++)
			{
				if (operation[i] == ' ')
				{
					index = atof(operation.substr(i + 1).c_str());
					break;
				}
			}
			string target_eq = equations[index - 1];
			vector<pair<string,string>>thequation= equation_i(target_eq);
			//print(thequation);
			print_equ_i(thequation);
			rhs = "";
		}
		else if (operation[0] == 'c')
		{
			string target;
			for (int i = 0; i < operation.size(); i++)
			{
				if (operation[i] == ' ')
				{
					target = operation.substr(i + 1);
					break;
				}
			}
			vector<string> v= coloumn(target, equations);
			print(v);
		}
		else if (operation[0] == 'a')
		{
			int index1 = operation.find(" ");
			int index2 = operation.rfind(" ");
			string t1 = operation.substr(index1 + 1, index2 - index1 - 1);
			string t2 = operation.substr(index2 + 1);
			float a = atof(t1.c_str());
			float b = atof(t2.c_str());
			add(a , b , equations);
		}
		else if (operation.substr(0, idx) == "subtract")
		{
			int index1 = operation.find(" ");
			int index2 = operation.rfind(" ");
			string t1 = operation.substr(index1 + 1, index2 - index1 - 1);
			string t2 = operation.substr(index2 + 1);
			float a = atof(t1.c_str());
			float b = atof(t2.c_str());
			subtract(a, b, equations);
		}
		else if (operation.substr(0, idx) == "substitute")
		{
			string word = operation.substr(idx + 1);
			int first = word.find(" ");
			int second = word.rfind(" ");
			string var = word.substr(0, first);
			string a = word.substr(first+1, second);
			string b = word.substr(second + 1);
			//substitute("x2", 1, 3, equations);
			substitute(var, atof(a.c_str()), atof(b.c_str()), equations);
		}
		else if (operation == "D")
		{
			d(equations);
			slice(equations);		
			print_D(equations.size(), num_vars(components));
		}
		else if (operation == "D_value")
		{
			d(equations);
			cout << D_value(determ, equations.size()) << endl;
		}
		else if (operation[0] == 'D' && operation.size() > 1)
		{
			string t = operation.substr(idx + 1);
			d_x(t, equations);
			slice(equations);
			print_D(equations.size(), num_vars(components));
		}
		else if (operation == "solve")
		{
			solve(equations);
		}

		getline(cin, operation);
	}

	return 0;
}



void slice(vector<string>equations)
{
	string temp;
	for (int i = 0; i < equations.size(); i++)
	{
		string s = equations[i];
		for (int j = 0; j < s.size(); j++)
		{
			if (s[j] == '+' || s[j] == '-')
			{
				components.push_back(temp);
				temp = "";
			}
			else if (s[j] == '=')
			{
				components.push_back(temp);
				components.push_back("=");
				temp = "";
			}
			else
			{
				temp += s[j];
			}
		}
	}
}

int num_vars(vector<string> components)
{
	set<string>st;
	for (int i = 0; i < components.size(); i++)
	{
		string s = components[i];
		for (int j = 0; j < s.size(); j++)
		{
			if ( (s[j] >= '0' && s[j] <= '9') || s[j] == '=') continue;
			else
			{
				st.insert(s.substr(j));
				break;
			}
		}
	}

	return st.size();
}

vector<pair<string,string>> equation_i(string eq)
{
	//cout << "equation passed to equation_i : " << eq << endl << endl;
	vector<string>lhs;  // left hand side
	vector<string>rhs;  // right hand side
	vector<pair <string, string> > v;  // vector of pairs to store coeff associated with their vars

	string temp;
	bool before_equal = 1;
	char sign = '+';
	int i = 0;
	if (eq[0] == '+') i += 1;
	else if (eq[0] == '-')
	{
		i += 1;
		sign = '-';
	}
	for (i; i <= eq.size(); i++)
	{

		if (eq[i] == '+' || eq[i] == '-' || eq[i] == '=' || i == eq.size())
		{
			if (before_equal)
			{
				if (is_num(temp))
				{
					if (sign == '+')
					{
						rhs.push_back("-" + temp);
						temp = "";
					}
					else
					{
						rhs.push_back("+" + temp);
						temp = "";
					}
				}
				else
				{
					lhs.push_back(sign + temp);
					temp = "";
				}
			}
			else
			{
				if (is_num(temp))
				{
					rhs.push_back(sign + temp);
					temp = "";
				}
				else
				{
					if (sign == '+')
					{
						lhs.push_back('-' + temp);
						temp = "";
					}
					else
					{
						lhs.push_back('+' + temp);
						temp = "";
					}
				}
			}
			if (eq[i] == '+')sign = '+';
			else if (eq[i] == '-')sign = '-';
			else if (eq[i] == '=')
			{
				before_equal = 0;
				if (eq[i + 1] == '+')
				{
					sign = '+';
					i++;
				}
				else if (eq[i + 1] == '-')
				{
					sign = '-';
					i++;
				}
				else
				{
					sign = '+';
					//i++;
				}
			}
		}

		else
		{
			temp += eq[i];
		}
	}
	
	
	for (int i = 0; i < lhs.size(); i++) // tazbetet el lhs
	{
		string s = lhs[i]; // current equation
		string num = "";
		bool flag = 1;
		for (int j = 0; j < s.size(); j++)
		{
			if ((s[j] >= '0' && s[j] <= '9') || s[j] == '.' || s[j] == '+' || s[j] == '-')
			{
				if (flag) num += s[j];
				else
				{
					v.push_back(make_pair(num, s.substr(j)));
					break;
				}
			}
			else
			{
				num += s[j];
				flag = 0;
				if (j == s.size() - 1) v.push_back(make_pair(num, ""));
				//v.push_back(make_pair(num, s.substr(j)));
				//num = "";
			}
		}
	}

	//print(v);


	// first sort alphabitacally by taking the first elemnet in each pair and divide it (num,name)and put it in
	// another pair , sort it , and copy the result to the original pair
	/*vector<pair <string, string> > a = sortAlpha(v);
	cout << "a : " << endl;
	print(a);

	for (int i = 0; i < a.size(); i++)
	{
		v[i].first = a[i].first + a[i].second;
	}*/
	sort(v.begin(), v.end(), compare);
	//cout << "after sorting alpha : " << endl;  de

	// second sort by rank  , by partially sort each variable eg: (alpha1 , alpha2,beta1,beta2)
	sortRank(v);
	//print(v);
	vector<pair <string, string> > result = compute_duplicates(v);

	//print(result);
	compute_rhs(rhs);
	return result;
}

vector<string> coloumn(string s, vector<string>equations)
{
	vector<string>col;
	for (int i = 0; i < equations.size(); i++)
	{
		int flag = 1;
		vector<pair<string, string>>current = equation_i(equations[i]);
		for (int j = 0; j < current.size(); j++)
		{
			//cout << to_str(current[j].first) << endl;
			if (s == to_str(current[j].first) + current[j].second)
			{
				float temp = atof(current[j].first.c_str());
				col.push_back(to_str(temp));
				flag = 0;
				break;
			}
		}
		//cout << endl << endl;
		if (flag == 1) col.push_back("0");
	}
	return col;
}

void add(int a, int b , vector<string>equations)
{
	float temp = 0;
	string rs;
	vector<pair<string, string>>e1 = equation_i(equations[a-1]);
	temp += atof(rhs.c_str());
	vector<pair<string, string>>e2 = equation_i(equations[b-1]);
	temp += atof(rhs.c_str());
	set<string>st;
	vector<string> vars;
	for (int i = 0; i < e1.size(); i++)
	{
		st.insert(to_str(e1[i].first) + e1[i].second);
	}
	for (int i = 0; i < e2.size(); i++)
	{
		st.insert(to_str(e2[i].first) + e2[i].second);
	}
	for (auto s : st)
	{
		vars.push_back(s);
	}
	sort(vars.begin(), vars.end(), sort_set);
	
	vector<string>current;
	for (int i = 0; i < vars.size(); i++)
	{
		current = coloumn(vars[i], equations);
		float sum = atof(current[a - 1].c_str()) + atof(current[b - 1].c_str());

		if (sum > 0 && i>0) cout <<"+"<< to_str(sum) << vars[i];
		else if (sum > 0)  cout << to_str(sum) << vars[i];
		else if (sum < 0)   cout << to_str(sum) << vars[i];
	}
	cout << "=";
	cout << to_str(temp) << endl;
}

void subtract(int a, int b, vector<string>equations)
{
	float temp = 0;
	string rs;
	vector<pair<string, string>>e1 = equation_i(equations[a - 1]);
	temp = atof(rhs.c_str());
	vector<pair<string, string>>e2 = equation_i(equations[b - 1]);
	temp -= atof(rhs.c_str());
	set<string>st;
	vector<string> vars;
	for (int i = 0; i < e1.size(); i++)
	{
		st.insert(to_str(e1[i].first) + e1[i].second);
	}
	for (int i = 0; i < e2.size(); i++)
	{
		st.insert(to_str(e2[i].first) + e2[i].second);
	}
	for (auto s : st)
	{
		vars.push_back(s);
	}
	sort(vars.begin(), vars.end(), sort_set);

	vector<string>current;
	for (int i = 0; i < vars.size(); i++)
	{
		current = coloumn(vars[i], equations);
		float sum = atof(current[a - 1].c_str()) - atof(current[b - 1].c_str());

		if (sum > 0 && i>0) cout << "+" << to_str(sum) << vars[i];
		else if (sum > 0)  cout << to_str(sum) << vars[i];
		else if (sum < 0)   cout << to_str(sum) << vars[i];
	}
	cout << "=";
	cout << to_str(temp)<<endl;
}

void substitute(string var, int a, int b, vector<string> equations)
{
	vector<pair<string, string>> e1 = equation_i(equations[a - 1]);
	string rs1 = rhs;
	vector<pair<string, string>> e2 = equation_i(equations[b - 1]);
	string rs2 = rhs;
	int index = 0;
	float coff;
	for (int i = 0; i < e2.size(); i++)
	{
		if (var == to_str(e2[i].first) + e2[i].second)
		{
			coff = atof(e2[i].first.c_str());  // hold the coeff of the substituted variable
			break;
		}
	}

	float factor;
	for (int i = 0; i < e1.size(); i++)
	{
		if (var == to_str(e1[i].first) + e1[i].second)
		{
			factor = atof(e1[i].first.c_str());  // hold the coeff of the substituted variable
			index = i;
			break;
		}
	}

	vector<pair<string, string>> equiv_value;
	for (int i = 0; i < e2.size(); i++)
	{
		if (i != index)
		{
			float temp = factor*( -1 * atof(e2[i].first.c_str())) / coff;
			string first = to_str(temp) + to_str(e2[i].first);
			equiv_value.push_back(make_pair(first , e2[i].second));
		}
	}

	string equation;
	//equation += rs2;
	for (int i = 0; i < e1.size(); i++)
	{
		if (i == index)
		{
			for (int j = 0; j < equiv_value.size(); j++)
			{
				if (atof(equiv_value[j].first.c_str()) > 0)
				{
					equation += '+';
					equation += equiv_value[j].first + equiv_value[j].second;
				}
				else
				{
					equation += equiv_value[j].first + equiv_value[j].second;
				}
			}
			
		}
		else
		{
			if (atof(e1[i].first.c_str()) > 0)
			{
				equation += '+';
				equation += e1[i].first + e1[i].second;
			}
			else
			{
				equation += e1[i].first + e1[i].second;
			}
		}
	}
	float resultant = atof(rs1.c_str()) - factor*(atof(rs2.c_str()) / coff);
	equation += "=" + to_str(resultant);
	//cout << "the equation is : " << equation << endl;
	vector<pair<string, string>>ans = equation_i(equation);
	//print(ans);
	print_equ_i(ans);
	
	
}

void d(vector<string> equations)
{
	set<string>st;
	for (int i = 0; i < equations.size(); i++)
	{
		vector<pair<string, string>>current = equation_i(equations[i]);
		for (int j = 0; j < current.size(); j++)
		{
			string temp = to_str(current[j].first) + current[j].second;
			st.insert(temp);
		}
	}

	vector<string>vars;
	for (auto c : st)
	{
		vars.push_back(c);
	}
	sort(vars.begin(), vars.end(), sort_set);

	for (int i = 0; i < vars.size(); i++)
	{
		vector<string>col = coloumn(vars[i], equations);
		for (int j = 0; j < col.size(); j++)
		{
			determ[j][i] = atof(col[j].c_str());
		}
	}

}

void d_x(string s, vector<string> equations)
{
	set<string>st; 
	vector<string>rs;
	for (int i = 0; i < equations.size(); i++)
	{
		vector<pair<string, string>>current = equation_i(equations[i]);
		rs.push_back(rhs);
		for (int j = 0; j < current.size(); j++)
		{
			string temp = to_str(current[j].first) + current[j].second;
			st.insert(temp);
		}
	}

	vector<string>vars;
	for (auto c : st)
	{
		vars.push_back(c);
	}
	sort(vars.begin(), vars.end(), sort_set);

	for (int i = 0; i < vars.size(); i++)
	{
		vector<string>col = coloumn(vars[i], equations);
		for (int j = 0; j < col.size(); j++)
		{
			if (vars[i] == s) determ[j][i] = atof(rs[j].c_str());
			else
			{
				determ[j][i] = atof(col[j].c_str());			
			}
		}
	}


}

float D_value(float a[100][100], int n)
{
	int det = 0, p, h, k, i, j; float temp[100][100];
	if (n == 1) {
		return a[0][0];
	}
	else if (n == 2) {
		det = (a[0][0] * a[1][1] - a[0][1] * a[1][0]);
		return det;
	}
	else {
		for (p = 0; p<n; p++) {
			h = 0;
			k = 0;
			for (i = 1; i<n; i++) {
				for (j = 0; j<n; j++) {
					if (j == p) {
						continue;
					}
					temp[h][k] = a[i][j];
					k++;
					if (k == n - 1) {
						h++;
						k = 0;
					}
				}
			}
			det = det + a[0][p] * pow(-1, p)*D_value(temp, n - 1);
		}
		return det;
	}
}

void solve(vector<string>equations)
{
	float delta;
	d(equations);
	delta = D_value(determ, equations.size()); // delta value

	set<string>st;
	vector<string>rs;
	for (int i = 0; i < equations.size(); i++)
	{
		vector<pair<string, string>>current = equation_i(equations[i]);
		rs.push_back(rhs);
		for (int j = 0; j < current.size(); j++)
		{
			string temp = to_str(current[j].first) + current[j].second;
			st.insert(temp);
		}
	}

	vector<string>vars;
	for (auto c : st)
	{
		vars.push_back(c);
	}
	sort(vars.begin(), vars.end(), sort_set);

	for (int i = 0; i < vars.size(); i++)
	{
		d_x(vars[i], equations);
		float dx = D_value(determ, equations.size());
		cout << vars[i] << "=" << dx/delta << endl;
	}

}