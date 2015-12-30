// 1.3.3_Permutations.cpp : Defines the entry point for the console application.
//

#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip> 
#include <sstream>
#include <algorithm>
#include <map>
#include <climits>

//typedef  unsigned char uchar;

using namespace std;

void printVector(const vector<pair<char, bool>> & tokens) {
	for (auto i = tokens.begin(); i != tokens.end(); ++i)
		cout << (*i).first << ((*i).second ? "* " : " ");
}


template<typename I>
void printWithSpaces(const string head, I begin, I end) {
	cout << head << endl;
	for (; begin != end; ++begin) {
		cout << *begin << " ";
	}
	cout << endl;
}

//A1
void initialProcessing(const string src, vector<pair<char, bool>> & tokens) {
	tokens.clear();
	char c = 0;
	for (string::const_iterator i = src.begin(); i != src.end(); ++i) {
		switch (*i) {
		case '(':
			tokens.push_back(make_pair(*i, true));
			while (++i < src.end() && *i == ' ');
			tokens.push_back(make_pair(*i, false));
			c = *i;
			break;
		case ' ':
			continue;
			break;
		case ')':
			assert(c != 0);
			tokens.push_back(make_pair(c, true));
			break;
		default:
			tokens.push_back(make_pair(*i, false));
			break;
		}
	}

	cout << "Preparation res: ";
	printVector(tokens);
	cout << endl;
}

void initialProcessing(const string src, vector<unsigned char> & tokens) {
	tokens.clear();
	for (string::const_iterator i = src.begin(); i != src.end(); ++i) {
		if (*i == ' ')
			continue;
		tokens.push_back(*i);	
	}
	printWithSpaces("Preparation res: ", tokens.begin(), tokens.end());
}


void seekNextUnmarked(vector<pair<char, bool>>::iterator & pos, const vector<pair<char, bool>>::iterator & end) {

	while (pos != end) {
		if (!(*pos).second){
			return;
		}
		pos++;
	}
	return;
}

template <class I>
void seekNextNotBracket(I & pos,const I end) {
	while (pos != end && (*pos++).first == '(');
	return;
}

string logStateStr(vector<char>::const_iterator& begin, vector<char>::const_iterator& end) {
	ostringstream oss;
	while (begin != end) {
		oss << *begin++ << " ";
	}
	return oss.str();
}

void logState(vector<char>::const_iterator& begin, vector<char>::const_iterator& end) {
	cout << "Current result:\n";
	cout << logStateStr(begin, end);
	cout << endl;
}

string resToStr(const map<unsigned char, unsigned char>& result) {
	ostringstream oss;
	for(map<unsigned char, unsigned char>::const_iterator i = result.begin(); i != result.end(); i++) 	{
		oss << (*i).first << "->" << (*i).second << " ";
	}
	return oss.str();
}

void solvePerm(string src, vector<char>& result) {

	vector<pair<char, bool>> tokens;
	initialProcessing(src, tokens);

	vector<pair<char, bool>>::iterator pos(tokens.begin());
	char cur, start;

	seekNextUnmarked(pos, tokens.end());

	while (pos != tokens.end()) {
		result.push_back('(');
		result.push_back((*pos).first);
		(*pos).second = true;
		start = (*pos).first;
		seekNextNotBracket(pos, tokens.end());
		cur = (*pos).first;
		pos++;

		while (1) {
			//STEP 4 (begin)
			for (; pos != tokens.end() && (*pos).first != cur; ++pos);
			//STEP 5
			if (pos == tokens.end()){
				if (cur != start) {
					result.push_back(cur);
					pos = tokens.begin();
					continue;
				}
				else {
					result.push_back(')');
					break;
				}
			}

			//STEP 4 (end)
			if (cur == (*pos).first) {
				(*pos).second = true;
			}

			seekNextNotBracket(pos, tokens.end());
			cur = (*pos).first;
			pos++;
		}

		pos = tokens.begin();
		seekNextUnmarked(pos, tokens.end());
	}

	return;
}

void testSolvePerm() {
	cout << "BEGIN testSolvePerm" << endl;
	vector<string> perms;
	vector<string> goals;

	perms.push_back("( a c f g ) ( b c d ) ( a e d ) ( f a d e )( b g f a e)");
	perms.push_back("( a e b ) ( c f ) ( d ) ( a b f c d e )");
	goals.push_back("( a d g ) ( c e b ) ( f )");
	goals.push_back("( a ) ( e f d ) ( b ) ( c )");
	assert(perms.size() == goals.size());
	for (auto i = perms.begin(), goal = goals.begin(); i != perms.end(); ++i, ++goal) {
		vector<char> result;

		cout << "Source permutation: " << *i << endl;
		solvePerm(*i, result);

		ostringstream oss;
		for (size_t i = 0; i < result.size() - 1; i++) {
			oss << result[i] << " ";
		}
		oss << result[result.size() - 1];

		string r = oss.str();
		cout << "Goal:   " << *goal << endl;
		cout << "Result: " << r << endl;
		assert(r == *goal);
	}
	cout << "TEST PASSED" << endl;
	cout << "END testSolvePerm" << endl;
}

void reversePermutationInPlace(vector<int> & perm) {
	//STEP1
	int m = perm.size();
	int j = -1;
	int i;

	while (m > 0) {
		//STEP2
		i = perm[m - 1];
		//STEP3
		while (i >= 0) {//STEP4
			perm[m - 1] = j;
			j = -m;
			m = i;
			i = perm[m - 1];
			if (i < 0)
				i = j;
		}
		perm[m - 1] = -i;
		//STEP6
		m--;
	}

	return;
}

void reversePermutationInPlaceZeroBased(vector<int> & perm) {
	//STEP1
	int m = perm.size() - 1;
	int j = -1;
	int i;

	while (m >= 0) {
		//STEP2
		i = perm[m];
		//STEP3
		while (i >= 0) {//STEP4
			perm[m] = j;
			j = m ? -m : INT_MIN;
			m = i;
			i = perm[m];
			if (i < 0)
				i = j;
		}
		perm[m] = i == INT_MIN ? 0 : -i;
		//STEP6
		m--;
	}

	return;
}


//#define NOT_ZERO_BASED

void testReversePermutation() {
	cout << "BEGIN testReversePermutation" << endl;
	vector<vector<int> > perms;
	vector<vector<int> > expected;
	void (*reverseFunction)(vector<int>&); 
#ifdef NOT_ZERO_BASED
	perms.push_back( vector<int> ({ 6, 2, 1, 5, 4, 3 }));
	expected.push_back(vector<int> ({ 3, 2, 6, 5, 4, 1 }));
	reverseFunction = reversePermutationInPlace;
#else
	perms.push_back( vector<int> ({ 5, 1, 0, 4, 3, 2 }) );
	expected.push_back(vector<int> ({ 2, 1, 5, 4, 3, 0 }));
	reverseFunction = reversePermutationInPlaceZeroBased;
#endif
	assert(perms.size() == expected.size());

	for (vector<vector<int>>::iterator i = perms.begin(), j = expected.begin(); i != perms.end(); ++i, ++j) {
		vector<int> permCopy(*i);
		printWithSpaces("Src permutation:", permCopy.begin(), permCopy.end());
		reverseFunction(permCopy);
		printWithSpaces("Result: ", permCopy.begin(), permCopy.end());
		printWithSpaces("Expected: ", (*j).begin(), (*j).end());
		assert(equal(permCopy.begin(), permCopy.end(), (*j).begin()));
	}
	cout << "TEST PASSED" << endl;
	cout << "END testReversePermutation" << endl;
}

void multiplyPermutationSinglePass(string src, map<unsigned char, unsigned char>& result) {
	result.clear();
	//XXX
	for (unsigned char i = 'a'; i <= 'g'; ++i) {
		result[i] = i;
	}
	unsigned char j = -1;
	unsigned char z = 0;

	for (auto m = src.rbegin(); m != src.rend(); ++m) {
		switch (*m){
		case ' ':
			continue;
		case ')'://STEP2.1
			z = 0;
			break;
		case '('://STEP2.2
			result[j] = z;
			break;
		default://STEP3
			swap(z, result[*m]);
			if (result[*m] == 0) {
				j = *m;
			}
			break;
		}
	}
}

void testMultiplyPermutationSinglePass() {
	cout << "Start testMultiplyPermutationSinglePass" << endl;
	vector<string> perms;
	vector<string> goals;

	perms.push_back("( a c f g ) ( b c d ) ( a e d ) ( f a d e )( b g f a e)");
	goals.push_back("d c e g b f a");

	perms.push_back("( a e b ) ( c f ) ( d ) ( a b f c d e )");
	goals.push_back("a b c e f d g");
	assert(perms.size() == goals.size());

	for (auto i = perms.begin(), goal = goals.begin(); i != perms.end(); ++i, ++goal) {
		map<unsigned char, unsigned char> result;

		cout << "Source permutation: " << *i << endl;
		multiplyPermutationSinglePass(*i, result);

		ostringstream oss;
		for (unsigned char  i = 'a'; i < 'g'; i++) {
			oss << result[i] << " ";
		}
		oss << result['g'];

		string r = oss.str();
		cout << "Goal:   " << *goal << endl;
		cout << "Result: " << r << endl;
		assert(*goal == r);
	}

	cout << "TEST PASSED" << endl;
	cout << "END testMultiplyPermutationSinglePass" << endl;
}

int main(int argc, char* argv[])
{
	if (argc == 1) {
		//testSolvePerm();
		//testReversePermutation();
		testMultiplyPermutationSinglePass();
	}
	return 0;
}

