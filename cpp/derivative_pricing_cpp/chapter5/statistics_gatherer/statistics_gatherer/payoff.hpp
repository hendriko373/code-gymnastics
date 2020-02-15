#ifndef  PAYOFF_HPP
#define  PAYOFF_HPP

class Payoff    // Abstract class
{
    friend class PayoffBridge;

public:
    virtual ~Payoff(){}

    virtual double operator()(double spot) const =0;
    
protected:
    virtual Payoff* clone() const =0;
    
private:
};

class PayoffCall : public Payoff
{
public:
    PayoffCall(double strike);
    virtual ~PayoffCall(){}
    
virtual double operator()(double spot) const;
    
protected:
    virtual PayoffCall* clone() const;

private:
    double strike_;
};

class PayoffPut : public Payoff
{
public:
    PayoffPut(double strike);
    virtual ~PayoffPut(){}

    virtual double operator()(double spot) const;
    
protected:
    virtual PayoffPut* clone() const;

private:
    double strike_;
};

class PayoffDoubleDig : public Payoff
{
public:
    PayoffDoubleDig(double lowBarrier, double highBarrier);
    ~PayoffDoubleDig(){}

    virtual double operator()(double spot) const;

protected:
    virtual PayoffDoubleDig* clone() const;
    
private:
    double lowBarrier_;
    double highBarrier_;
};

#endif   /* ----- #ifndef PAYOFF_HPP ----- */
