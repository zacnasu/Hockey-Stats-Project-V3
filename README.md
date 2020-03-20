# Wolves-Stats-Project-V3

This was a project created to help automate taking hockey stats. It tracks stats shift by shift and counts shots on goal, shots, missed shots, and scoring Opportunities.

The data comes in the form:
(Player1) (Player2) (Player3) (Player4) (Player5) (Shots on Goal for) (Missed Shots for) (Scoring Opportunities for) (Shots on Goal Against) (Missed Shots Against) (Scoring Opportunities Against)

Each Game has three input files, ES for even strength, PP for powerplay, and PK for penalty-kill.  Each input file also has an output file that contains a table in latex format. The even strength table file has each players' corsi, percentage of scoring opportunities, shots on goal for per shift, scoring opportunities for per shift, shots on goal against per shift, scoring opportunities against per shift, and shift count. In addition, the powerplay table has each players' shots on goal for per shift and scoring opportunities for per shift. And finally the penalty kill table has each players' shots on goal against per shift and scoring opportunites against pers shift


It also tracks the shifts for the player and checks the shift before to avoid double counting. 

