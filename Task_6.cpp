#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

vector<string> wrapText( string &inputText, int lineLength)
{
    vector<string> wrappedLines;
    istringstream inputStream(inputText);
    string currentWord, currentLine;

    while (inputStream >> currentWord)
    {
        if (currentLine.size() + currentWord.size() + 1 <= lineLength)
        {
            if (!currentLine.empty())
            {
                currentLine += ' ';
            }
            currentLine += currentWord;
        }
        else
        {
            wrappedLines.push_back(currentLine);
            currentLine.clear();
            currentLine += currentWord;
        }
    }

    if (!currentLine.empty())
    {
        wrappedLines.push_back(currentLine);
    }

    return wrappedLines;
}

int main()
{
    string textToWrap = "Mary loves to sing and perform tapdancing.";
    int desiredLineLength = 9;

    vector<string> wrappedText = wrapText(textToWrap, desiredLineLength);

    for (int lineNum = 0; lineNum < wrappedText.size(); ++lineNum)
    {
        cout << wrappedText[lineNum] << endl;
    }

    return 0;
}
