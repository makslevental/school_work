def hotel_cost(nights):
    return nights * 140

bill = hotel_cost(5)

def add_monthly_interest(balance):
    print str(balance * (1 + (0.15 / 12))) + "bob"
    return balance * (1 + (0.15 / 12))

def make_payment(payment, balance):
    l = (balance-payment)
    k = add_monthly_interest(l)
    print "You still owe: %d" % k
    return k
    
payment = bill/2
bill = make_payment(payment, bill)
payment = 100
print make_payment(payment, bill)

    