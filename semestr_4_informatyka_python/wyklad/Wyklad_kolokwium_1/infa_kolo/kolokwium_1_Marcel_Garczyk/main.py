import math

def procedura(R,L,C,f,switch):
    w = 0
    if switch == True:
        w = 1.0/(4 * (math.pi**2) * (f**2) * L)
        return w
    else:
        w = math.radians (math.atan(2*math.pi*f*L-((1.0/(2*math.pi*f*C)))/R))
    return w

I=6
N=7
R=I*10
L=N*10**(-5)
A=8
f=(I+N+A)*10**3
C=(A+1)*10**(-6)
switch=False
print(procedura(R,L,C,f,switch))