#include <iostream>
#include <stack>
#include <cctype>
#include <string>

using namespace std;

struct TreeNode
{
    char data;
    TreeNode *leftChild;
    TreeNode *rightChild;

    TreeNode(char value) : data(value), leftChild(nullptr), rightChild(nullptr) {}
};

TreeNode *createTreeNode(char value)
{
    return new TreeNode(value);
}

bool isOperator(char character)
{
    return character == '+' || character == '-' || character == '*' || character == '/';
}

bool isOperand(char ch)
{
    return isdigit(ch) || (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

bool checkFullyParenthesized(const string &expression)
{
    stack<char> s;
    bool lastWasOperator = false, lastWasOperand = false, lastWasClose = false;

    for (int i = 0; i < expression.length(); i++)
    {
        char ch = expression[i];

        if (isspace(ch))
            continue;

        if (ch == '(')
        {
            if (lastWasOperand || lastWasClose)
            {
                return false;
            }
            s.push(ch);
            lastWasOperator = lastWasOperand = lastWasClose = false;
        }
        else if (ch == ')')
        {
            if (lastWasOperator || s.empty())
            {
                return false;
            }
            s.pop();
            lastWasClose = true;
            lastWasOperand = lastWasOperator = false;
        }
        else if (isOperator(ch))
        {
            if (!lastWasOperand && !lastWasClose)
            {
                return false;
            }
            lastWasOperator = true;
            lastWasOperand = lastWasClose = false;
        }
        else if (isOperand(ch))
        {
            if (lastWasOperand || lastWasClose)
            {
                return false;
            }
            lastWasOperand = true;
            lastWasOperator = lastWasClose = false;
        }
        else
        {
            return false;
        }
    }

    return s.empty();
}

TreeNode *buildExpressionTree(const string &expression)
{
    stack<TreeNode *> nodesStack;
    stack<char> operatorsStack;

    for (int index = 0; index < expression.length(); index++)
    {
        char currentChar = expression[index];
        if (isspace(currentChar))
            continue;

        if (isdigit(currentChar))
        {
            nodesStack.push(createTreeNode(currentChar));
        }
        else if (currentChar == '(')
        {
            operatorsStack.push(currentChar);
        }
        else if (currentChar == ')')
        {
            while (!operatorsStack.empty() && operatorsStack.top() != '(')
            {
                TreeNode *operatorNode = createTreeNode(operatorsStack.top());
                operatorsStack.pop();

                operatorNode->rightChild = nodesStack.top();
                nodesStack.pop();
                operatorNode->leftChild = nodesStack.top();
                nodesStack.pop();
                nodesStack.push(operatorNode);
            }
            operatorsStack.pop();
        }
        else if (isOperator(currentChar))
        {
            while (!operatorsStack.empty() && isOperator(operatorsStack.top()))
            {
                TreeNode *operatorNode = createTreeNode(operatorsStack.top());
                operatorsStack.pop();

                operatorNode->rightChild = nodesStack.top();
                nodesStack.pop();
                operatorNode->leftChild = nodesStack.top();
                nodesStack.pop();
                nodesStack.push(operatorNode);
            }
            operatorsStack.push(currentChar);
        }
    }

    while (!operatorsStack.empty())
    {
        TreeNode *operatorNode = createTreeNode(operatorsStack.top());
        operatorsStack.pop();

        operatorNode->rightChild = nodesStack.top();
        nodesStack.pop();
        operatorNode->leftChild = nodesStack.top();
        nodesStack.pop();
        nodesStack.push(operatorNode);
    }

    return nodesStack.top();
}

void printTree(TreeNode *rootNode, int indent = 0)
{
    if (rootNode == nullptr)
        return;
    printTree(rootNode->rightChild, indent + 4);
    cout << string(indent, ' ') << rootNode->data << "\n";
    printTree(rootNode->leftChild, indent + 4);
}

int computeTreeValue(TreeNode *rootNode)
{
    if (rootNode == nullptr)
        return 0;
    if (!rootNode->leftChild && !rootNode->rightChild)
    {
        return rootNode->data - '0';
    }
    int leftValue = computeTreeValue(rootNode->leftChild);
    int rightValue = computeTreeValue(rootNode->rightChild);
    switch (rootNode->data)
    {
    case '+':
        return leftValue + rightValue;
    case '-':
        return leftValue - rightValue;
    case '*':
        return leftValue * rightValue;
    case '/':
        return leftValue / rightValue;
    }
    return 0;
}

int main()
{
    string inputExpression;
    cout << "Enter a fully parenthesized arithmetic expression: ";
    getline(cin, inputExpression);

    if (!checkFullyParenthesized(inputExpression))
    {
        cout << "The input is not a valid fully parenthesized arithmetic expression." << endl;
        return 1;
    }

    TreeNode *expressionRoot = buildExpressionTree(inputExpression);
    cout << "Binary Expression Tree (Tree Displayed Horizontally):" << endl;
    printTree(expressionRoot);
    int finalResult = computeTreeValue(expressionRoot);
    cout << "Value at root: " << finalResult << endl;

    return 0;
}
