# תכנות מערכות 2 מטלה 2
4 ספרות אחרונות של ת"ז: 1536

מייל: yairjacob620@gmail.com
## **אופן המימוש והחלוקה בקוד**
הגרף מומש על ידי **מחלקה** `Graph` בעוד שהאלגוריתמים נמצאים ב-**namespace** שנקרא `Algorithms`. שניהם נמצאים ב-namespace בשם `ex1`. דוקומנטציה מפורטת על כל הפונקציות/משתנים נמצאת בקוד עצמו.

בנוסף לקבצים ההכרחיים (`Algorithms.cpp, Algorithms.hpp, Graph.cpp, Graph.hpp`), קיימים גם הקבצים `tests.cpp, main.cpp` המשומשים ליצירת קבצי הרצה, קובץ `makefile` המתאים להם וגם הקובץ `doctest.h` שמשומש לטסטים.
## הרצה של הקוד
דרך טרמינל שנפתח בתיקייה עם כל 8 הקבצים, ניתן להריץ את הפקודות הבאות:

| Command | Description |
| ---------- | ---------- |
| `make` or `make main` | Creates and runs an executable called `main` that runs all of the required 7 functions* on a certain graph. Also performs some arithmetic and conditional on graphs. The graph (or rather the adjacency matrix) is in main.cpp, and can be changed to see how it affects the outputs of the functions.|
| `make tests` | Creates and runs a doctest executable called `tests` that runs dozens of tests on the required 7 functions and all of the arithmetic and conditional operators** on graphs. Prints a summary of the tests. |
| `make clean` | Deletes all .o files and executables. |

*תזכורת: 7 הפונקציות הנחוצות (למטלה) הן: 

`g.loadGraph(), g.printGraph(), isConnected(g), shortestPath(g, src, dest), isContainsCycle(g), isBipartite(g), negativeCycle(g)`

**ה-overloaded operators הם (19 סה"כ):

'<', '>', '==', '!=', '<=', '>=', '+', '-', '+' (urinary), '-' (urinary), '+=', '-=', '++Graph', 'Graph++', '--Graph', 'Graph--', '* scalar', '* Graph', '<< Graph' (output).

## מידע נוסף על הקוד והמימוש
1) במימוש זה לא מתקבלים גרפים שבהם צלעות מקודקוד לעצמו (ייזרקו על כך שגיאות מתאימות). עקב כך, כפל בין גרפים ייתן גרף שמטריצת השכנויות שלו היא מכפלה של המטריצות המייצגות של שני הגרפים - אך שאלכסונה הראשי מורכב מאפסים במקום הערכים המקוריים המתקבלים מהמכפלה.
3) כל צלע בגרף נחשבת לממושקלת, וצלעות יכולות להיות בעלי משקלים חיוביים, שליליים, או 0, כאשר אי-קיום צלע בין שני קודקודים יזוהה על ידי הערך הקבוע `INF` במקום המתאים במטריצת השכנויות של הגרף (דוגמה למטריצת שכנויות תקינה קיימת ב-`main.cpp`). עקב כך, בחישוב ערך של תא בכפל בין מטריצות - כאשר לפחות אחד הגורמים הוא INF התוצאה תמיד תהיה INF.
4) גרפים מכוונים שבהם לכל צלע קיימת צלע לכיוון השני עם אותו משקל ייחשבו כגרפים לא-מכוונים.
5) חלק מהאלגוריתמים מחזירים משתנה בוליאני בלבד, בעוד שמידע נוסף אודות התוצאות שלהם מודפס ב-standard output stream (ב-`std::cout`). כמובן שכל המידע שמודפס יכול גם להיות מוחזר בדרך כלשהי, אך לדעתי זאת הדרך הפשוטה והיעילה ביותר להחזיר את מידע זה.
