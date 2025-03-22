# שרשר - srsr
זה כלי עבור שירשור קבצי וידאו באמצעות FFPMEG
הכלי מקל את השימוש, במקום לרשום פקודה ארוכה ב-bash,
ניתן להוסיף את שם התיקייה בה רוצים שהוידאו המאוחד ישמר ולאחר מכן להוסיף את קטעי הוידאו כאשר רווח מפריד בין כל קטע.
הכלי הזה כרגע מסתמך על נתיב מקומי מסויים ואינו מיועד להתקנה כללית, אלא אם כן משנים את הנתיב (לתיקיית העבודה הנוכחית, למשל).
## English
This tool is meant to ease the use of ffmpeg concatination.
It's not meant to be installed on any machine, is it currently uses a local path, hardcoded to it.
If someone wants to use it, the path needs be altered (to CWD, for instance), and only then compiled.
Also, it relies on my own library for a function that assist printing error messages.
