# airport_c_project


# NAME
    This program is a functionning airport simulation (AirSim). 
    You can add, delete and advance in time to observe the behaviour of the scheduled flights

# COMMANDS
    exit
        closes the program
    
    timewarp [n]
    tw [n]
        advance n minutes in the future

    clear
        clear console

    add
        -t <add plane to takeoff queue>
        -l <add plane to landing queue>
    
    ls 
        --takeoff <display takeoff queue>
        -t
        
        --landing <display landing queue>
        -l

        --blacklist <display blacklist>
        -b

        --companies <display company list>
        -c

        --comp-caracteristics [acronym] <display caracteristics of specified company>
        -cc
    
    land
    ld
        --number [n] <land plane N°n>
        -n [n]
        
        --index [i] <land the ith plane in landing queue>
        -i [i]

        --emergency
        -!
            --number [n] <land plane N°n in emergency>
            -n [n]
            
            --index [i] <land the ith plane in landing queue in emergency>
            -i [i]

    del
        --takeoff
        -t
            --number [n] <remove plane N°n from takeoff queue>
            -n [n]
            
            --index [i] <remove the ith plane from takeoff queue>
            -i [i]

        --landing
        -l
            --number [n] <remove plane N°n from landing queue>
            -n [n]
            
            --index [i] <remove the ith plane from landing queue>
            -i [i]
    
    info

        --takeoff <display detailed info of planes in takeoff queue>
        -t
        
        --landing <display detailed info of planes in landing queue>
        -l

        --all <displays detailed info of all the planes>
        -a 
    
    blacklist
    bl
        --add [acronym] <add specified company to the blacklist>
        -a [acronym]

        --remove [acronym] <remove specified company from the blacklist>
        -r [acronym]

    man
        display this page

# BUGS
    All known bugs are now corrected.

# AUTHOR
   De Castro Lucas - 2A - Class 23
   Da Silva Lucas - 2A - Class 23

# COPYRIGHT
    This program is under the MIT Copyright license.
