#include <iostream>
class Context;

class State {
protected:
	Context *context_;
public:
	virtual ~State() {}
	void setContext(Context* context) {
		this->context_ = context;
	};

	virtual void Handle() = 0;
};

class Context {
private:
	State *state_;
public:
	Context(State* state) : state_(nullptr) {
		this->transTo(state);
	}
	~Context() {
		delete state_;
	}

	void transTo(State *state) {
		this->state_ = state;
		this->state_->setContext(this);
	}

	void Handle() {
		this->state_->Handle();
	}	
};

class ConcreteStateA : public State {
 public:
	 void Handle() override;
	 ConcreteStateA()
	 {

  }
  ~ConcreteStateA() {
	
  }
};

class ConcreteStateB : public State {
 public:
  void Handle() override {
    std::cout << "ConcreteStateB handles request1.\n";
  }
  ConcreteStateB() {

  }
~ConcreteStateB() {

}
};

void ConcreteStateA::Handle() {
  {
    std::cout << "ConcreteStateA handles request1.\n";
    std::cout << "ConcreteStateA wants to change the state of the context.\n";

    this->context_->transTo(new ConcreteStateB);
  }
}

/**
 * The client code.
 */
void ClientCode() {
  Context *context = new Context(new ConcreteStateA);
  context->Handle();
  context->Handle();
  delete context;
}

int main() {
  ClientCode();
  return 0;
}