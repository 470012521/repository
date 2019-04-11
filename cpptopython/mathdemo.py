#!/usr/local/anaconda3/bin/python
#Filename:math_test.py
import extend as ext
import datetime
import math

def getDoubleSharkFinPrice(price, rf, vol, times, terms, expiry, returnL, returnU, rebateL, rebateU, barrierPriceL,
                           barrierPriceU, strikeL, strikeU, stkcode, beginDate, endDate, tpye=4):
    tua = expiry
    payoff = 0.00

    naturalDays = datetime.datetime.strptime(endDate, "%Y-%m-%d") - datetime.datetime.strptime(beginDate, "%Y-%m-%d")
    naturalDaysInt = int(naturalDays.days) + 1
    print('naturalDays:', naturalDaysInt)
    # S means all price path
    S = ext.getPricePathByNumpy(price, vol, tua, naturalDaysInt, times, rf)

    # option pricing module
    for finalValue in S[naturalDaysInt]:
        if finalValue >= barrierPriceU:
            payoff += rebateU

        elif finalValue >= strikeU and finalValue < barrierPriceU:
            payoff += (finalValue - strikeU) * returnU / (barrierPriceU - strikeU)

        elif finalValue > strikeL and finalValue < strikeU:
            payoff += 0

        elif finalValue > barrierPriceL and finalValue <= strikeL:
            payoff += (strikeL - finalValue) * returnL / (strikeL - barrierPriceL)

        else:
            payoff += rebateL

    value = math.exp(-rf * tua) * payoff / times

    return str(value)