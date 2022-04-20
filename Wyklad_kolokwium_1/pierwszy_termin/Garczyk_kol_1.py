def f(I, O):
	p = 0
	k = 0
	O.append(I[0])
	while O[-1]*O[-1] < 50:
		T = []
		j = 0
		for i in I[1::]:
			if not i % O[p] == 0:
				T.append(i)
				j += 1
		I = T
		k += 1
		p += 1
		O.append(I[0])
	print(I)
	print(O)
	print(O[4]-I[0])


I = []
for i in range(2,51):
	I.append(i)
O = []
f(I, O)
