# MyCalc C++ sample app using STL

The sample application with the following idea behind:
if we have a lot of complicated calculations it is not a bad idea to keep 
calculation results in memory cash for use them later as result of the same next calculation.
Of course,it is useful only if every calculation will take more time 
as put/get values into/from the cash. This is C++ realization, but similarly it
can be done in Java (see project JMyCalc).

Different SimpleCash realizations  are considered:

 - std::map _cash and conditional locking (SimpleCash).
 - std::vector<Cell> _cash and conditional locking (SimpleCash1).
 - std::vector<Cell> _cash and conditional locking, but improved Add() function (SimpleCash2).
 - the same as SimpleCash2, but with locking only in add() function (SimpleCash3, 10x faster).
 - using std::list container for _cash and with locking only in add() function (SimpleCash4).
