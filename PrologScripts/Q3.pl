% Rules
is_Object(X):-cup(X).

% This rule is just an example
is_Object(X):-bottle(X).

% Last condition isnt necessary, but it is a good practice to include it I believe
obj_hasColor(X,Y):-(is_Object(X), color(Y), hasColor(X, Y)).

% Facts
cup(c1).
color(white).
hasColor(c1, white).