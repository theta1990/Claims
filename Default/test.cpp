#include <Theron/Theron.h>

class Actor : public Theron::Actor
{
public:

    explicit Actor(Theron::Framework &framework) : Theron::Actor(framework)
    {
        RegisterHandler(this, &Actor::Handler);
    }

private:

    void Handler(const int &message, const Theron::Address from)
    {
        Send(message, from);
    }
};

int main()
{
    Theron::Receiver receiver;
    Theron::Framework framework;
    Actor actor(framework);

    framework.Send(int(0), receiver.GetAddress(), actor.GetAddress());

    receiver.Wait();
} 
