% Browsing
% File name should be inputed as 'name.txt' and end with a full stop

browse:-
    seeing(Old),
    see(user),
    write('Enter the name of the file to browse: '),
    read(File),
    see(File),
    repeat,
    read(Data),
    process(Data),
    seen,
    see(Old),
    !.
    
process(end_of_file):- !.
process(Data):- 
    write(Data),
    nl,
    fail.
    

% Save the current prolog program in memory to a file
% File name should be inputed as 'name.txt' and end with a full stop
    
mySave:-
    write('Enter the name of the file to be written to: '),
    read(File),
    telling(Old),
    tell(File),
    listing,
    told,
    tell(Old).