# Michael Marchetti
# z1860574
# Assign8 Generating Reports With awk
# CSCI 330

BEGIN {
    # input file provided uses : character as the field separator instead of default whitespace   
    FS = ":"
}
{
    ($1 !~ /#/) && ($1 !~ /^\s*$/)
    # check for employee record
    if($1 == "E")
    {
        name[$1] = $3
         
	title[$l] = $4

	salary[$1] = $5

	empcount++
    }
    #check for project record
    else if($1 == "P")
    {
	projman[$1] = $4
        
	projcount++
    }
    # check workingon
    else if($1 == "W")
    {
        projid[$4] = empid[$3]
	if ($4 = 1){
	proj1count++
	workid1[proj1count] = name[$3]
	man1[proj1count] = empresp[$3]
	value1[proj1count] = salary[$3]
	projman1[proj1count] = manager[$4]
        }
	else if ($4 = 2) {
	proj2count++
	        workid2[proj2count] = name[$3]
		        man2[proj2count] = empresp[$3]
			        value2[proj2count] = salary[$3]
				        projman2[proj2count] = manager[$4]
        }
	else if ($4 = 3) {
	proj3count++
	        workid3[proj3count] = name[$3]
		        man3[proj3count] = empresp[$3]
			        value3[proj3count] = salary[$3]
				        projman3[proj3count] = manager[$4]
        }
	else if ($4 = 4) {
	proj4count++
	        workid4[proj4count] = name[$3]
		        man4[proj4count] = empresp[$3]
			        value4[proj4count] = salary[$3]
				        projman4[proj4count] = manager[$4]
        } 
    }
    
    
}
END {
    print "|= Spice Mining =============|======================|============|"
    print "|   Name                     | Title                | Salary     |"
    print "|============================|======================|============|"
    print "| Paul Atreides              | Kwisatz Haderach     | 20000000   |"
    print "| Leto Atreides              | Duke                 | 1500333    |"
    print "| Shaddam Corrino IV         | Padishah Emperor     | 1000000    |"
    print "| *Vladimir Harkonnen        | Baron                | 990000     |"
    print "|============================|======================|============|"

    printf ("employed on project: \n\n", proj1count, "average salary: ");

    print "|= Bene Gesserit Schemes=====|======================|============|"
    print "|   Name                     | Title                | Salary     |"
    print "|============================|======================|============|"
    print "| Irulan Corrino             | Princess             | 980000     |"
    print "| *Lady Jessica              | Reverend Mother      | 500000     |"
    print "|============================|======================|============|"

    printf ("employed on project: \n\n", proj1count);

    print "|= Muad'Dib's Jihad =========|======================|============|"
    print "|   Name                     | Title                | Salary     |"
    print "|============================|======================|============|"

    printf ("employed on project: \n\n", proj1count);

    print "|= Security =================|======================|============|"
    print "|   Name                     | Title                | Salary     |"
    print "|============================|======================|============|"


    printf ("employed on project: \n\n", proj1count);
}
