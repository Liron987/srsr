#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>

#include "../tifkudim.h"

#define ANSI_COLOR_ADOM     "\x1b[31m"
#define ANSI_COLOR_ADOM_BHIR     "\x1b[1;31m"
#define ANSI_COLOR_YROK_BHIR     "\x1b[1;32m"
#define ANSI_COLOR_ZHOV     "\x1b[0;33m"
#define ANSI_COLOR_ZHOV_BHIR     "\x1b[1;33m"
#define ANSI_COLOR_CHOL     "\x1b[0;34m"
#define ANSI_COLOR_CHOL_BHIR     "\x1b[1;34m"
#define ANSI_COLOR_RESET   "\x1b[0m"


int main (int mis, char **tiun) {

    unsigned short ys_mikum = 0;

    // במקרה שאין מספיק טיעונים, נדפיס הערה בונה:
    if (mis < 3) {
        printf(
            ANSI_COLOR_ADOM_BHIR
            "   :חסרים לך טיעונים בפקודה! אתה חייב לכלול לפחות\n"
            "1. srsr :שם התוכנה  \n"
            "2. (אם תשמיט נתון זה, ברירת המחדל זה תיקיית הורדות) [נתיב תיקיית היעד]\n"
            "3. לפחות 2 קבצים אותם אתה מעוניין לשרשר\n"
            ANSI_COLOR_RESET
        );

        return 1;
    }

    // נייצר המיקום המתאים:
    char mikum[512];

    if
    (
        strstr(tiun[1], ".mp4") == NULL
        && strstr(tiun[1], ".m4v") == NULL
        && strstr(tiun[1], ".ts") == NULL
    ) {
        snprintf(mikum, sizeof(mikum), tiun[1]);

        ys_mikum = 1;
    } else {
        printf(
            ANSI_COLOR_ZHOV_BHIR
            "  שים לב! הטיעון השני בפקודה חייב להיות תיקיית יעד\n"
            "  מכיוון שלא הכנסת תיקיית יעד, הברירת מחדל זה תיקיית העבודה הנוכחית\n"
            ANSI_COLOR_RESET
        );

        //sprintf(mikum, "/media/USB/MyPassport/MyPassport/הורדות");
        if (getcwd(mikum, sizeof(mikum) ) == NULL)
        {
            fprintf(stderr, "%s; לא הצלחתי להשיג את תיקיית העבודה הנוכחית, יוצא\n", KST() );
            exit(1);
        }

    }

    // נוודא שכל הטיעונים מכילים לפחות כמות מסויימת של תוים וגם מפ4 / מ4ו / טס
    for (unsigned short h = 1 + ys_mikum; h < mis; h++) {
        if (strlen(tiun[h]) < 5) {
            printf(
                ANSI_COLOR_ADOM_BHIR
                "\nאחד הטיעונים קצר מדי וכנראה לא מכיל שם תקני: טיעון מספר %d\n"
                ANSI_COLOR_RESET
                , h);

            return 1;
        }

        if
        (
            strstr(tiun[h], ".mp4") == NULL
            && strstr(tiun[h], ".m4v") == NULL
            && strstr(tiun[h], ".ts") == NULL
        ) {
            printf(
                ANSI_COLOR_ADOM_BHIR
                "\nאחד הטיעונים חסר '.מפ4' וכנראה לא מכיל שם תקני: טיעון מספר %d\n"
                ANSI_COLOR_RESET
                , h);

            return 1;
        }
    }

    // נייצר קובץ מלל במיקום המתאים ונכיל בו את השורות הקשורות:
    FILE *mk;

    // לפני שנכתוב לקובץ נוודא שאנו לא דורסים בטעות קובץ קיים:
    if ((mk = fopen("/media/USB/MyPassport/MyPassport/הורדות/t.txt", "r") ) != NULL) {

        fclose(mk);

        printf(
            ANSI_COLOR_ZHOV
            "\n  ?שים לב! אתה עומד לדרוס קובץ מלל קיים, האם להמשיך\n"
            " 1 = כן\n"
            " לא = 2 או כל תו אחר\n"
            ANSI_COLOR_RESET
        );

        char tsuva[8] = {0};
        if (scanf("%s", tsuva) <= 0) {
            printf(
                ANSI_COLOR_ADOM_BHIR
                "\nלא החזרת תשובה תקפה, יוצא...\n"
                ANSI_COLOR_RESET
            );

            return 1;
        }

        if (tsuva[0] == '1') {

            printf(
                ANSI_COLOR_YROK_BHIR
                "\nממשיך בפעולה\n"
                ANSI_COLOR_RESET
            );

        } else {

            printf(
                ANSI_COLOR_ADOM_BHIR
                "\nעוצר הפעולה!\n"
                ANSI_COLOR_RESET
            );

            return 1;
        }

    }

    if ( (mk = fopen("/media/USB/MyPassport/MyPassport/הורדות/t.txt", "w") ) == NULL) {
        printf(
            ANSI_COLOR_ADOM_BHIR
            "\nלא הצלחתי ליצור קובץ עבור השרשור\n"
            ANSI_COLOR_RESET
        );

        return 1;
    }

    for (unsigned short h = 1 + ys_mikum; h < mis; h++) {

        char hozz[256];
        snprintf(hozz, sizeof(hozz), "file '%s'\n", tiun[h]);

        fputs(hozz, mk);
    }


    fclose(mk);

/*
    // נייצר את שרשיר הסרטים בהתאם לצרכי פפמאג:
    char srsir[8192] = { 0 };
    for (unsigned short h = 1 + ys_mikum; h < mis; h++)
    {
        int orc = snprintf(srsir + strlen(srsir), sizeof(srsir), "%s|", tiun[h]);

        if (orc != (int)strlen(tiun[h]) + (int)strlen("|") )
        {
            fprintf
            (
                stderr,
                ANSI_COLOR_ADOM_BHIR
                "%s; אין מספיק מקום בשרשיר עבור כל המחרוזות סרטים, יוצא\n"
                "orc = %d, (int)strlen(tiun[h]) = %d\n"
                ANSI_COLOR_RESET,
                KST(), orc, (int)strlen(tiun[h])
            );
            exit(1);
        }
    }

    if (srsir[strlen(srsir) - 1] == '|')
        srsir[strlen(srsir) - 1] = '\0';
*/

    // ניקח את שם הקובץ:
    char sm[256] = {0};
    unsigned short orc = strlen(tiun[2]),
                   mikum_hnkuda = 4;
    for (unsigned short h = orc, btihut = 0; h > 0; h--, btihut++) {

        // נוודא שהשם נכנס במשתנה:
        if(btihut >= sizeof(sm) - 1) {
            printf(
                ANSI_COLOR_ADOM_BHIR
                "\nשם הקובץ גדול מדי עבור המשתנה המכיל, עוצר הפעולה!\n"
                ANSI_COLOR_RESET
            );

            return 1;
        }

        if (tiun[1 + ys_mikum][h] == '.')
            mikum_hnkuda = orc - h;

        if (tiun[1 + ys_mikum][h] == '/') {
            h++;
            memcpy(sm, tiun[1 + ys_mikum] + h, orc - h - mikum_hnkuda);

            break;
        }
    }
    printf
    (
        ANSI_COLOR_YROK_BHIR
        "\nשם = %s"
        ANSI_COLOR_RESET
        "\n"
        , sm
    );

    if (sm[0] == '-')
    {
        int8_t orc_sm = strlen(sm);
        memmove(sm + 1, sm, orc_sm);
        sm[0] = '\\';

        printf
        (
            ANSI_COLOR_YROK_BHIR
            "\nשם שונה = %s"
            ANSI_COLOR_RESET
            "\n"
            , sm
        );
    }


    // נייצר ונפעיל הפקודה

    char pkuda[2048];
    snprintf(pkuda, sizeof(pkuda), "cd '%s' && ffmpeg -f concat -safe 0 -i /media/USB/MyPassport/MyPassport/הורדות/t.txt -c copy '%s -srsr.mp4'"
             ,mikum, sm);
/*
    char pkuda[10240];
    snprintf
    (
        pkuda, sizeof(pkuda),
        "cd '%s' && "
        "ffmpeg -i \"concat:%s\" -c copy '%s -srsr.mp4'"
        ,mikum, srsir, sm
     );
*/
    printf(
            "\n" ANSI_COLOR_CHOL_BHIR
            "פקודה = "
            ANSI_COLOR_RESET "%s\n\n", pkuda
           );

    if (system(pkuda) == -1) {
        perror("Sgia bhozat hpkuda:" );
        return 2;
    }


    printf(
        ANSI_COLOR_ZHOV_BHIR
        "\n  מוחק את קובץ המלל  \n"
        ANSI_COLOR_RESET
    );
    remove("/media/USB/MyPassport/MyPassport/הורדות/t.txt");

    // נחזיר השם לקדמותו המקורית
    if (sm[0] == '\\')
    {
        printf(
            ANSI_COLOR_ZHOV_BHIR
            "\n  מחזיר שם ששונה לקדמותו:  \n"
            ANSI_COLOR_RESET
        );


        char sm_ysn[256],
             sm_hds[256];

        if (snprintf(sm_ysn, sizeof(sm_ysn), "%s/%s -srsr.mp4", mikum, sm) < 0)
            perror("לא הצלחתי להכניס השם הישן למשתנה");

        if (snprintf(sm_hds, sizeof(sm_hds), "%s/%s -srsr.mp4", mikum, sm + 1) < 0)
            perror("לא הצלחתי להכניס השם החדש למשתנה");

        printf("שם ישן = %s\n שם חדש = %s\n\n", sm_ysn, sm_hds);

        if (rename(sm_ysn, sm_hds) ^ 0)
            perror("שגיאה בשינוי השם");


        printf(
            ANSI_COLOR_YROK_BHIR
            "\n  השם הוחזר לקדמותו בהצלחה  \n"
            ANSI_COLOR_RESET
        );
    }

/*
 *
 * printf(
        ANSI_COLOR_YROK_BHIR
        "\n  מוחק את קבצי הוידאו  \n"
        ANSI_COLOR_RESET
    );
    for (unsigned short h = 1 + ys_mikum; h < mis; h++) {

        remove(tiun[h]);
    }
*/

    printf
    (
        "\n" ANSI_COLOR_YROK_BHIR
        "  :בדוק שהתוצאה לשביעות רצונך\n"
        ANSI_COLOR_RESET
        "   %s/%s\n"
        ANSI_COLOR_YROK_BHIR
        "ומחק את קבצי המקור"
        ANSI_COLOR_RESET "\n\n"
        , mikum, sm
    );


    return 0;
}
