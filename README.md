## Purpose
In order to create animations I need to preseve a hierarchy of bones and parts of a model in form of a tree.
Alternatively it can be achived using directed acyclic graph, but I decided to choose tree instead, because of its simplicity.
There is need to create and change hierarchy of model's parts dependently.
It can be achived concatening transformations during traversal of structure.
I could not find any implementation which whould be flexible enough.
I decided that it was great opportunity to reinvent the wheel.
