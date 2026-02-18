
time = int(input("DELAY TIME (ms)= "))
i = int(input("1 MC = (6 or 12) CLK : "))

if(i == 6):
    clk = 1/18.432
    mc = round(clk,3) * i
elif(i == 12):
    clk = 1/11.0592
    mc = round(clk,3) * i


nmc = round((time *1000) / mc)
print("Calculate NMC :", format(nmc, ","))

s = int(input("S = "))
u = int(input("U = "))
t = int(input("T = "))


h = (nmc - 3*s - 3*(s*u) - 3*(s*u*t) - 19) / (2 * (s*u*t))
h = round(h)

calmc = 2*s*u*t*h + 3*s*u*t + 3*s*u + 3*s + 19
ctime = (calmc * mc) / 1000

print("Calculate H :",h)
print("Calculate MC :", format(calmc, ","))
print("Calculate Time:",ctime)
