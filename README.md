# Sorting_Algorithm_Visualiser

(S)orting_(A)lgorithm_(V)isualiser with a built in interpretter

Interpretter Folder contains a skeleton that was used to implement the interpretter into SAV.

The finished interpretter is built in into SAV.

Consult the documentation to learn more about the interpretter.


////////////////////////////////////////////////
////////INFORMAL OVERVIEW OF THE PROJECT////////


https://youtu.be/mnFT7NYmNsc - overview

https://youtu.be/d_AS1_mZR78 - visualiser code

https://youtu.be/9ScfOO42qZU - interpretter code


///////////////////////////////////////////////

i =1

while (i<10)

swap(ar[0], ar[s-i])

i=i+1

end while

u=1

while (u<10)

if(ar[0] >= ar[s-u])
u=u
end if
u=u+1
end while

end program


///////////////////////////////

u=s-1

while(u>0)

i = 0

while (i<u)

if(ar[i]>ar[i+1])
swap(ar[i],ar[i+1])
endif
i=i+1

end while

u=u-1

end while
end program

/////////////////////////////////


i =0
j=0

while(i<s-1)

jMin = i
j= i+1
	while (j<s)
		if(ar[j]<ar[jMin])
		jMin = j
		end if
	j = j+1
	end while
	if(jMin != i)
		swap(ar[i], ar[jMin])
	end if
i=i+1
end while
end program



