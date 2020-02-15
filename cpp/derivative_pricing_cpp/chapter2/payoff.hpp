#ifndef PAYOFF_HPP
#define PAYOFF_HPP

class Payoff {
public:
    enum OptionType {
        call, put,
        digitalCall, digitalPut,
        doubleDigital,
        forward};

    Payoff(double strike, OptionType optionType);
    Payoff(double barrierOne, double barrierTwo, OptionType optionType);

    // Calculate and return payoff for given spot
    double operator()(double spot) const;

private:
    double strike_;
    double strikeTwo_;
    OptionType optionType_;
};

#endif
