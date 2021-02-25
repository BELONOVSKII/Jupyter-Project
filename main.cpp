
/// 1) Define an alias VecStrings for the std::vector<std::string> datatype
/// using the typedef keyword.
///
/// 2) Create a function called toCountSurvived that obtains an input stream
/// object (given by reference) istream& (input.csv), reads the whole file
/// line by line and saves surnames ("Braund; Mr. Owen Harris" will be just
/// "Braund") of survived people from input.csv (Survived column).
/// The function returns data of type VecStrings -- vector of surnames of survivors.
///
/// Use intermediate functions in task 2 to do the following:
/// 2.1) Extract data (surname and whether the person survived or not) from one line of input.
/// 2.2) Extract surname from a string containing full name.
/// 
///
/// 3) Create a function printVec.
/// The function prints the content of the given vector out to the standard output.
/// It should takes a vector as argument by reference and print the value of the 
/// elements as well as their enumeration.
/// 1) Name_1
/// 2) Name_2
/// ...
/// N) Name_n
///
///
///
/// 4) Create a function called getFareForClass that takes an input stream object
/// istream& and an integer number representing class (Pclass, 1 to 3), reads the stream 
/// until the end and returns the mean fare value of people of the given class.
/// The function returns a single value of type double -- the mean fair value.
/// Use at least two intermediate functions in problem 4.
///
///
/// Additional problems
///
/// 5) Create a function called genThreeDigitNumber(const int& randomState).
/// The function returns a random three digit number as std::string.
/// Use:
/// std::mt19937 gen(randomState);
/// std::uniform_int_distribution<int> distr(0,9);
/// int rNum = distr(gen); // random number
///
/// 6) Create a new vector newVec as VecStrings and fill it with random numbers.
/// newVec size should be the same as the size of the vector obtained from toCountSurvived
///
///
///   Workshop 8
///
/// 6) Reverse the vector containing names of surviving passengers using std::reverse.
/// Sort this vector using std::sort
/// Include library <algorithm> to access these functions.
///
/// 7) Implement a function printVecIter that takes two vector iterators as arguments
/// and prints the elements of the underlying vector. The iterators should represent
/// the start and the end of the vector.
///
/// 8) Use a regular iterator and a reverse iterator (.rbegin()) to print the vector 
/// containing survivor names in a straightforward order and in a reverse order
/// with the function printVecIter.
/// 
/// 9) Using the sorted list of surnames find the first and last surname that starts with
/// the letter "H".
/// Create a new vector and use functions std::find and std::copy to copy all surnames
/// starting with "H" into it.
///
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <random>
#include <algorithm>
using namespace std;
typedef std::vector<std::string> Row;
typedef std::vector<Row> Matrix;
Row toCountSurvived(std::istream& in);
Row vect_read(istream& in);
double getFareForClass(istream& in, int cl);
void printVector(const Row& vector, int k);
string genThreeDigitNumber(const int randomState);
bool sortSecond(string i, string j);
void printVecIter(Row::iterator i1, Row::iterator i2);
void printVecIterReverse(Row::reverse_iterator i1, Row::reverse_iterator i2);
//bool find1(Row::iterator)
int main ()
{

    const std::string INP_FILE_NAME = "../../../data/problem2_titanic/titanic.csv";
    std::ifstream input_file(INP_FILE_NAME);
    string header;
    getline(input_file, header);
    stringstream ssh(header);
//    printVector(vect_read(ssh));
    cout << '\n' << '\n';
    Row v1 = toCountSurvived(input_file);
//    cout << "-----------\n";


    cout << v1.size() << endl;
//    cout << *(v1.begin()) << '\t' << *(v1.end()-1) << endl;
    printVector(v1,5);
    reverse(v1.begin(), v1.end());
    cout << '\n';
    printVector(v1, 5);
    sort(v1.begin(), v1.end());
//    sort(v1.begin(), v1.end(), greater<>());
//    sort(v1.begin(), v1.end(), sortSecond);
    cout << '\n';
//    printVecIter(v1.begin(), v1.begin()+20);
//    cout << '\n';
//    printVecIterReverse(v1.rbegin(), v1.rbegin()+20);

    Row::iterator i = find(v1.begin(), v1.end(), "Behr");
    cout << *i << endl;
//    printVector(v1, 10);
//    input_file.close();
//    input_file.open(INP_FILE_NAME);
//    getline(input_file, header);
//    cout << getFareForClass(input_file, 3);
//    Row newvec(v1.size());
//    int inc = 0;
//    for (string& x:newvec)
//    {
//        x = genThreeDigitNumber(inc++);
//    }
//    for (const string& x:newvec)
//    {
//    cout << x << ' ';
//    }
//    input_file.open(INP_FILE_NAME);
//    input_file.clear();
//    input_file.open(INP_FILE_NAME)
}
Row toCountSurvived(std::istream& in)
{
    string s;
    Row surnames;
    while (std::getline(in, s))
    {
        stringstream ss(s);
        Row vector = vect_read(ss);
        if (vector[1] == "1")
        {
            stringstream ss2(vector[3]);
            string surname;
            getline(ss2, surname, ';');
            surnames.push_back(surname);

        }
    }
    return surnames;
}
Row vect_read(istream& in)
{
    string s;
    Row vector;
    while (getline(in, s, ','))
    {
        vector.push_back(s);
    }
    return vector;
}
void printVector(const Row& vector, int k)
{
    int i = 0;
    for (const string s:vector)
    {
        if (i < k)
            cout << s << endl;
        ++i;
    }
}
double getFareForClass(istream& in, int cl)
{
    string s;
    double sum = 0;
    double k = 0;
    while (std::getline(in, s))
    {
        stringstream ss(s);
        Row vector = vect_read(ss);
        if (stoi(vector[2]) == cl)
        {
            stringstream ss2(vector[9]);
            double tmp;
            ss2 >> tmp;
            sum += tmp;
            ++k;
        }
    }
    return sum/k;
}
string genThreeDigitNumber(const int randomState)
{
    std::mt19937 gen(randomState);
    stringstream ss;
    std::uniform_int_distribution<int> distr(0,9);
    for ( int i = 0; i < 3; ++i)
    {
        int rNum = distr(gen);
        while ((i == 0) && (rNum == 0))
            rNum = distr(gen);
        ss << rNum;
    }
    return ss.str();
}
bool sortSecond(string i, string j)
{
    return i[1] < j[1];
}
void printVecIter(Row::iterator i1, Row::iterator i2)
{
    for (Row::iterator i=i1; i!=i2;++i)
    {
        cout << *i<< ' ';
    }
}
void printVecIterReverse(Row::reverse_iterator i1, Row::reverse_iterator i2)
{
    for (Row::reverse_iterator i=i1; i!=i2;++i)
    {
        cout << *i<< ' ';
    }
}
