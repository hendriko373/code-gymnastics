#ifndef  PAYOFF_HPP
#define  PAYOFF_HPP

class Payoff    // Abstract class
{
public:
    virtual Payoff* clone() const =0;
    virtual ~Payoff(){}

    virtual double operator()(double spot) const =0;
};

class PayoffCall : public Payoff
{
public:
    PayoffCall(double strike);
    virtual PayoffCall* clone() const;

    virtual double operator()(double spot) const;

private:
    double strike_;
};

class PayoffPut : public Payoff
{
public:
    PayoffPut(double strike);
    virtual PayoffPut* clone() const;

    virtual double operator()(double spot) const;

private:
    double strike_;
};

class PayoffDoubleDig : public Payoff
{
public:
    PayoffDoubleDig(double lowBarrier, double highBarrier);
    virtual PayoffDoubleDig* clone() const;

    virtual double operator()(double spot) const;
    
private:
    double lowBarrier_;
    double highBarrier_;
};

#endif   /* ----- #ifndef PAYOFF_HPP ----- */
