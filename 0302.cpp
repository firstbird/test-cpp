class MinStack
{

public:
	stack<int> s;
	stack<int> min_stack;
	/** initialize your data structure here. */
	MinStack()
	{
	}

	void push(int x)
	{
		s.push(x);
		if (min_stack.size() == 0)
		{
			min_stack.push(x);
		}
		else
		{
			min_stack.push(x < min_stack.top() ? x : min_stack.top());
		}
	}

	void pop()
	{
		s.pop();
		min_stack.pop();
	}

	int top()
	{
		return s.top();
	}

	int getMin()
	{
		return min_stack.top();
	}
};