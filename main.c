// C project 2i1
// Made by : Massinissa KANEM & Mathis MAGNE
// DATE : 16/01/2023
// Teacher : Frederic SANANES

#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>
#include <string.h>
#include <curl/curl.h>


static char *host = "localhost";
static char *user = "root";
static char *pass = "user";
static char hostcase[50];
static char *dbname = "massi";

unsigned int port = 3306;
static char *unix_socket = NULL;
unsigned int flag = 0;

int main(){

    int choice1;
    int choice2;
    int retour = 1;

    MYSQL *conn;
    conn = mysql_init(NULL);
    printf("###################################################################");
printf("\nBienvenue sur notre logiciel de genstion de bases de données\n");
printf("###################################################################\n\n");
    printf("Choisissez : ");
    printf("\n1- modifier une base de donnees existante.");
    printf("\n2- Creer une nouvelle base de donnees.");
    printf("\n3- Consulter la doc (curl).");
    printf("\nVotre choix : ");

    scanf("%d", &choice1);
    while(choice1 < 1 || choice1 > 3){
        printf("Choisissez : ");
        printf("\n1- modifier une base de donnees existante.");
        printf("\n2- Creer une nouvelle base de donnees.");
        printf("\n3- Consulter la doc (curl).");
        printf("\nVotre choix : ");
        scanf("%d", &choice1);
    }
//1
    if(choice1 == 1){

        printf("\nEntrez le nom  de la base de données à laquelle vous souhaitez vous connecter : ");
        scanf("%s", hostcase);
        fflush(stdout);

        if(!(mysql_real_connect(conn, host, user, pass,hostcase , 3306, NULL, 0)))
        {
            fprintf(stderr, "\nError: %s [%d]\n", mysql_error(conn), mysql_errno(conn));
            printf("\nBase de données mal orthographiée ou inexistante. Veuillez réessayer.\n\n");

        }else{
            printf("\nVous etes connectés a la base de donnée : %s !\n\n", hostcase);

            //choix commandes :
            int end = 1;

        while(end == 1){

                printf("Choisissez selon votre besoin : \n");
                printf("1- creation de base de données \n");
                printf("2- creation d'une table dans une base de données \n\n");

                printf("3- renommer une table \n");
                printf("4- Ajouter une colonne à une table \n");
                printf("5- renommer une colonne d'une table \n");
                printf("6- Remplir une table \n\n");

                printf("7- suppression de base de données \n");
                printf("8- supprimer une ligne d'une table \n");
                printf("9- supprimer une colonne d'une table \n");
                printf("10- supprimer une table \n\n");

                printf("11- affichage des résultats \n");
                printf("12- afficher les bases dans le serveur mysql \n");
                printf("13- afficher les tables d'une BDD \n\n");

                printf("14- faire un export d'une table \n");
                printf("15- Consulter la doc (curl) \n\n");
                printf("Votre choix : ");
                scanf("%d", &choice2);

                while(choice2 < 1 || choice2 > 16){

                        printf("Choisissez selon votre besoin : \n");
		        printf("1- creation de base de données \n");
		        printf("2- creation d'une table dans une base de données \n\n");

		        printf("3- renommer une table \n");
		        printf("4- Ajouter une colonne à une table \n");
		        printf("5- renommer une colonne d'une table \n");
		        printf("6- Remplir une table \n\n");

		        printf("7- suppression de base de données \n");
		        printf("8- supprimer une ligne d'une table \n");
		        printf("9- supprimer une colonne d'une table \n");
		        printf("10- supprimer une table \n\n");

		        printf("11- affichage des résultats \n");
		        printf("12- afficher les bases dans le serveur mysql \n");
		        printf("13- afficher les tables d'une BDD \n\n");

		        printf("14- faire un export d'une table \n");
		        printf("15- Consulter la doc (curl) \n\n");
		        printf("Votre choix : ");
		        scanf("%d", &choice2);

                }

                switch (choice2){
                    case 1: {
                        //create BDD

                        char bdd_name[258];
  			char query[256];

  			printf("Veuillez saisir le nom de la bdd a creer : \n");
  			scanf("%s", bdd_name);

  			snprintf(query, sizeof(query), "CREATE DATABASE %s", bdd_name);

  			if(mysql_query(conn, query)) {
    				fprintf(stderr, "\n%s\n", mysql_error(conn));
    				mysql_close(conn);
    				exit(1);
  			} else {
    				printf("\nBDD %s crée !", bdd_name);
    				mysql_close(conn);
  			}

                        printf("\n\nVoulez vous continuer ?");
                        printf("\n1- Oui");
                        printf("\n2- Non");
                        printf("\nvotre choix : ");
                        scanf("%d", &end);
                        if (end == 2) {
                            break;
                        }
                        break;
                    }
                    case 2:
                        //create TABLE

                        char table_name[256];
                        char query[256];

                        MYSQL* conn = mysql_init(NULL);
                        if (!mysql_real_connect(conn, host, user, pass,hostcase , 3306, NULL, 0)) {
                            fprintf(stderr, "%s\n", mysql_error(conn));
                            return 1;
                        }

                        printf("Entrez le nom de la table : ");
                        scanf("%s", table_name);
                        sprintf(query, "CREATE TABLE %s (id INT NOT NULL AUTO_INCREMENT PRIMARY KEY)", table_name);

                        if (mysql_query(conn, query)) {
                            fprintf(stderr, "%s\n", mysql_error(conn));
                            return 1;
                        }else{printf("Table %s crée avec succés ! ", table_name);}
                        mysql_close(conn);

                        printf("\n\nVoulez vous continuer ?");
                        printf("\n1- Oui");
                        printf("\n2- Non");
                        printf("\nvotre choix : ");
                        scanf("%d", &end);

                        if(end == 2){
                            break;
                        }
                        break;

                    case 3:
                        //rename table

                        char name[258];
                        char name_after[258];

                        printf("Veuillez saisir le nom de la table à modifier : \n");
                        scanf("%s", &name);
                        printf("Veuillez saisir le nouveau nom de table : \n");
                        scanf("%s", &name_after);

                        char query[256];
                        snprintf(query, sizeof(query), "RENAME TABLE %s TO %s", name, name_after);

                        if(mysql_query(conn, query))
                        {
                            fprintf(stderr, "\n%s\n", mysql_error(conn));
                            mysql_close(conn);
                            exit(1);
                        }else{printf("\nLa bdd %s est devenue %s !", name, name_after);exit(1);}

                        mysql_close(conn);

                        printf("\n\nVoulez vous continuer ?");
                        printf("\n1- Oui");
                        printf("\n2- Non");
                        printf("\nvotre choix : ");
                        scanf("%d", &end);

                        if(end == 2){
                        scanf("%d", &end);
                            break;
                        }
                        break;

                    case 4:
                        //Add column to table

                        char table_name[100];
                        char column_name[100];
                        char column_type[100];
                        int column_size;
                        int auto_increment;

                        printf("Enter the name of the table: ");
                        scanf("%s", table_name);

                        printf("Enter the name of the column: ");
                        scanf("%s", column_name);

                        printf("Enter the type of the column (e.g. INT, VARCHAR): ");
                        scanf("%s", column_type);

                        printf("Enter the size of the column: ");
                        scanf("%d", &column_size);

                        printf("En AUTO INCREMENT (1 pour oui / 0 pour non : ");
                        scanf("%d", &auto_increment);


                        char query[200];

                        if (auto_increment) {
                            sprintf(query, "ALTER TABLE %s ADD %s %s(%d) AUTO_INCREMENT PRIMARY KEY", table_name, column_name, column_type, column_size);
                        }else {
                            sprintf(query, "ALTER TABLE %s ADD %s %s(%d)", table_name, column_name, column_type, column_size);
                        }

                        if (mysql_query(conn, query)) {
                            fprintf(stderr, "%s\n", mysql_error(conn));
                            return 1;
                        }

                        mysql_close(conn);

                        printf("\n\nVoulez vous continuer ?");
                        printf("\n1- Oui");
                        printf("\n2- Non");
                        printf("\nvotre choix : ");
                        scanf("%d", &end);
                        if(end == 2){
                            break;
                        }
                        break;

                    case 5:
                        //rename column

                        MYSQL *conn;
                        MYSQL_RES *result;
                        MYSQL_ROW row;

                        char column[100];
                        char new_name[100];
                        char table[100];

                        printf("Enter the name of the table: ");
                        scanf("%s", table);
                        printf("Enter the name of the column you want to rename: ");
                        scanf("%s", column);
                        printf("Enter the new name for the column: ");
                        scanf("%s", new_name);

                        conn = mysql_init(NULL);
                        mysql_real_connect(conn, host, user, pass, hostcase, 3306,  NULL, 0);

                        char query[200];
                        sprintf(query, "ALTER TABLE %s CHANGE %s %s VARCHAR(255)", table, column, new_name);
                        mysql_query(conn, query);

                        result = mysql_store_result(conn);

                        printf("\nColonne renommée avec succès !\n");

                        mysql_free_result(result);
                        mysql_close(conn);

                        printf("\n\nVoulez vous continuer ?");
                        printf("\n1- Oui");
                        printf("\n2- Non");
                        printf("\nvotre choix : ");
                        if(end == 2){
                            break;
                        }

                    case 6:
                        //insert into table

                        char table_name[128];
                        char column_names[128];
                        char values[128];

                        printf("Entrez le nom de la table : ");
                        scanf("%s", table_name);

                        printf("Entrez les noms des colonnes dans lesquelles insérer, séparés par des virgules : ");
                        scanf("%s", column_names);

                        printf("Entrez les valeurs à insérer, séparées par des virgules : ");
                        scanf("%s", values);

                        char query[256];
                        snprintf(query, sizeof(query), "INSERT INTO %s (%s) VALUES (%s)", table_name, column_names, values);

                        if(mysql_query(conn, query))
                        {
                            fprintf(stderr, "\n%s\n", mysql_error(conn));
                            mysql_close(conn);
                            exit(1);
                        }else{printf("\nAjout à la table %s réussi !", table_name);exit(1);}

                        mysql_close(conn);

                        printf("\n\nVoulez vous continuer ?");
                        printf("\n1- Oui");
                        printf("\n2- Non");
                        printf("\nvotre choix : ");
                        scanf("%d", &end);

                        if(end == 2){
                            break;
                        }
                        break;

                    case 7:
                       //delete bdd
                        char bdd_name[258];

                        printf("Veuillez saisir le nom de la BASE a supprimer: \n");

                        char query[256];
                        snprintf(query, sizeof(query), "DROP DATABASE %s", bdd_name);

                        if(mysql_query(conn, query))
                        {
                            fprintf(stderr, "\n%s\n", mysql_error(conn));
                            mysql_close(conn);
                            exit(1);
                        }else{printf("\nBDD %s supprimée !", bdd_name);}
                        mysql_close(conn);

                        printf("\n\nVoulez vous continuer ?");
                        printf("\n1- Oui");
                        printf("\n2- Non");
                        printf("\nvotre choix : ");
                        scanf("%d", &end);

                        if(end == 2){
                            break;
                        }
                        break;

                    case 8:
                         //delete line

                        char table_name[256];
                        char delete_name[256];
                        char column_name[256];
                        int id_choice;
                        int row_id;


                        MYSQL* conn = mysql_init(NULL);
                        if (!mysql_real_connect(conn, host, user, pass, hostcase, 3306,  NULL, 0)) {
                            fprintf(stderr, "%s\n", mysql_error(conn));
                            return 1;
                        }

                        char query[256];

                        printf("Entrez le nom d'une table : ");
                        scanf("%s", table_name);
                        printf("Est ce que c'est la colonne id : ");
                        scanf("%d", &id_choice);
                        if(id_choice == 1){
                            printf("Entrez le nom de la colonne id : ");
                            scanf("%s", column_name);
                            printf("Entrez le numero de la ligne : ");
                            scanf("%d", row_id);

                            sprintf(query, "DELETE FROM %s WHERE %s=%d", table_name, column_name,row_id);
                            if (mysql_query(conn, query)) {
                                fprintf(stderr, "%s\n", mysql_error(conn));
                                return 1;
                            }else{printf("La ligne %d a bien ete supprimee de la table '%s' !\n", row_id, table_name);}
                        }else if(id_choice == 0){
                            printf("Entrez le nom de la colonne : ");
                            scanf("%s", column_name);
                            printf("Entrez le nom a supprimer : ");
                            scanf("%s", delete_name);

                            char query[256];
                            sprintf(query, "DELETE FROM %s WHERE %s=%s", table_name, column_name,delete_name);
                            if (mysql_query(conn, query)) {
                                fprintf(stderr, "%s\n", mysql_error(conn));
                                return 1;
                            }else{printf("La ligne avec la colonne %s et le contenu %s a bien ete supprimee de la table '%s' !\n", column_name, delete_name, table_name);}
                        }

                        mysql_close(conn);

                        printf("\n\nVoulez vous continuer ?");
                        printf("\n1- Oui");
                        printf("\n2- Non");
                        printf("\nvotre choix : ");
                        scanf("%d", &end);
                        if(end == 2){
                            break;
                        }

                    case 9:
                        //delete column

                        MYSQL_RES *res;
                        MYSQL_ROW row;

                        char table[50];
                        char column[50];
                        char query[200];
			int key;

                        printf("Entrez le nom de la table: ");
                        scanf("%s", table);
                        printf("Entrez le nom de la colonne que vous voulez supprimer : ");
                        scanf("%s", column);
			            printf("Est ce que c'est une clé primaire : ");
			            scanf("%s", &key);
                        if(key==1){
                            sprintf(query, "ALTER TABLE %s DROP PRIMARY KEY", table, column);
	                        if (mysql_query(conn, query)) {
        	                    fprintf(stderr, "%s\n", mysql_error(conn));
                	            exit(1);
                        	}printf("clé primaire supprimée !");
			            }else{
                        	sprintf(query, "ALTER TABLE %s DROP COLUMN %s", table, column);
	                        if (mysql_query(conn, query)) {
        	                    fprintf(stderr, "%s\n", mysql_error(conn));
                	            exit(1);
                        	}printf("Supprimée !");
			            }

                        mysql_free_result(res);
                        mysql_close(conn);

                        printf("\n\nVoulez vous continuer ?");
                        printf("\n1- Oui");
                        printf("\n2- Non");
                        printf("\nvotre choix : ");
                        scanf("%d", &end);

                        if(end == 2){
                            break;
                        }

                    case 10:
                        // delete table

                        MYSQL_RES *res;
                        MYSQL_ROW row;

			MYSQL* conn = mysql_init(NULL);
                        if (!mysql_real_connect(conn, host, user, pass, hostcase, 3306,  NULL, 0)) {
                            fprintf(stderr, "%s\n", mysql_error(conn));
                            return 1;
                        }

                        char table_name[100];
                        char query[200];

                        printf("Entez le nom de la table que vous voulez supprimer : ");
                        scanf("%s", table_name);

                        sprintf(query, "DROP TABLE %s", table_name);

                        if (mysql_query(conn, query))
                        {
                            fprintf(stderr, "%s\n", mysql_error(conn));
                            exit(1);
                        }else{printf("Supprimée avec succés !");}

                        mysql_close(conn);

                        printf("\n\nVoulez vous continuer ?");
                        printf("\n1- Oui");
                        printf("\n2- Non");
                        printf("\nvotre choix : ");
                        scanf("%d", &end);

                        if(end == 2){
                            break;
                        }

                        break;

                    case 11:
                       //select from table

                        char table_name[128];
                        char query[256];

                        printf("Entrez le nom de la table : ");
                        scanf("%s", table_name);

                        MYSQL *conn = mysql_init(NULL);

                        if (!mysql_real_connect(conn, host, user, pass,hostcase , 3306, NULL, 0))
                        {
                            fprintf(stderr, "Connexion a la bdd non reussi : Error %u (%s)\n", mysql_errno(conn), mysql_error(conn));
                            return 1;
                        }

                        snprintf(query, sizeof(query), "SELECT * FROM %s", table_name);

                        if (mysql_query(conn, query))
                        {
                            fprintf(stderr, "Échec d'exécution de la requête: Error %u (%s)\n", mysql_errno(conn), mysql_error(conn));
                            mysql_close(conn);
                            return 1;
                        }

                        MYSQL_RES *result = mysql_store_result(conn);

                        if (!result)
                        {
                            fprintf(stderr, "Échec de la récupération des résultats de la requête : Error %u (%s)\n", mysql_errno(conn), mysql_error(conn));
                            mysql_close(conn);
                            return 1;
                        }
                        int num_fields = mysql_num_fields(result);
                        MYSQL_FIELD *fields = mysql_fetch_fields(result);

                        // ligne de séparation
                        for (int i = 0; i < num_fields; i++) {
                            printf("--------------------");
                            printf("-+-");
                        }
                        printf("\n");

                        // noms des champs
                        for (int i = 0; i < num_fields; i++) {
                            printf("%-*s", 20, fields[i].name);
                            printf(" | ");
                        }
                        printf("\n");

                        // ligne de séparation
                        for (int i = 0; i < num_fields; i++) {
                            printf("--------------------");
                            printf("-+-");
                        }
                        printf("\n");

                        //définir la taille des cases à 20
                        MYSQL_ROW row;
                        while ((row = mysql_fetch_row(result)))
                        {
                            for (int i = 0; i < num_fields; i++)
                            {
                                printf("%-*s", 20, row[i]);
                                printf(" | ");
                            }
                            printf("\n");
                        }

                        // ligne de séparation
                        for (int i = 0; i < num_fields; i++) {
                            printf("--------------------");
                            printf("-+-");
                        }
                        printf("\n");

                        mysql_free_result(result);
                        mysql_close(conn);

                        printf("\n\nVoulez vous continuer ?");
                        printf("\n1- Oui");
                        printf("\n2- Non");
                        printf("\nvotre choix : ");
                        scanf("%d", &end);

                        if(end == 2){
                            break;
                        }
                        break;

                    case 12:
                        //list of BDDs

                        MYSQL *conn;
                        MYSQL_RES *res;
                        MYSQL_ROW row;
                        char *server = "localhost";
                        char *user = "root";
                        char *password = "user";

                        char query[258];

                        conn = mysql_init(NULL);

                        if (!mysql_real_connect(conn, server, user, password, hostcase, 3306, NULL, 0))
                        {
                            fprintf(stderr, "\n%s\n", mysql_error(conn));
                            exit(1);
                        }

                        sprintf(query, "SHOW DATABASES");
                        mysql_query(conn, query);
                        res = mysql_use_result(conn);

                        printf("Les BDD dans le serveur '%s': \n", server);
                        while ((row = mysql_fetch_row(res)) != NULL)
                        {
                            printf("- %s \n", row[0]);
                        }

                        mysql_free_result(res);
                        mysql_close(conn);

                        printf("\n\nVoulez vous continuer ?");
                        printf("\n1- Oui");
                        printf("\n2- Non");
                        printf("\nvotre choix : ");
                        scanf("%d", &end);

                        if(end == 2){
                            break;
                        }

                        break;

                    case 13:
                        //list of tables

                        MYSQL *conn;
                        MYSQL_RES *res;
                        MYSQL_ROW row;

                        char database[50];
                        char query[256];

                        printf("Entrez le nom de la bdd : ");
                        scanf("%s", database);

                        conn = mysql_init(NULL);

                        if (!mysql_real_connect(conn, host, user, pass, database, 3306,  NULL, 0))
                        {
                            fprintf(stderr, "\n%s\n", mysql_error(conn));
                            exit(1);
                        }

                        sprintf(query, "SHOW TABLES");
                        mysql_query(conn, query);
                        res = mysql_use_result(conn);

                        printf("Les tables dans la bdd '%s': \n", database);
                        while ((row = mysql_fetch_row(res)) != NULL)
                        {
                            printf("- %s \n", row[0]);
                        }

                        mysql_free_result(res);
                        mysql_close(conn);

                        printf("\n\nVoulez vous continuer ?");
                        printf("\n1- Oui");
                        printf("\n2- Non");
                        printf("\nvotre choix : ");
                        scanf("%d", &end);
                        if(end == 2){
                            break;
                        }
                        break;

                    case 14:
                        //export table

                        MYSQL* conn;
                        MYSQL_RES* res;
                        MYSQL_ROW row;

                        char* server = "localhost";
                        char* user = "root";
                        char* password = "user";
                        char* database = "massi";

                        conn = mysql_init(NULL);

                        if (!mysql_real_connect(conn, server, user, password, hostcase, 3306, NULL, 0)) {
                            fprintf(stderr, "%s\n", mysql_error(conn));
                            return 1;
                        }


                        char table_name[255];
                        printf("Enter the name of the table: ");
                        scanf("%s", table_name);


                        char query[255];
                        sprintf(query, "SELECT * FROM %s", table_name);
                        if (mysql_query(conn, query)) {
                            fprintf(stderr, "%s\n", mysql_error(conn));
                            return 1;
                        }


                        // Get the result set
                        res = mysql_use_result(conn);

                        // Open the file for writing
                        char file_name[255];
                        sprintf(file_name, "%s-table.txt", table_name);
                        FILE* fp;
                        fp = fopen(file_name, "w");
                        if (fp == NULL) {
                            fprintf(stderr, "Error opening file\n");
                            return 1;
                        }else{printf("\nTable exportée avec succes !");}


                        // Save the column names to the file
                        MYSQL_FIELD* field;
                        while ((field = mysql_fetch_field(res)) != NULL) {
                            fprintf(fp, "%-*s", 20, field->name);
                            fprintf(fp, " | ");
                        }
                        fprintf(fp, "\n");

                        // Print a dividing line
                        for (int i = 0; i < mysql_num_fields(res); i++) {
                            fprintf(fp, "--------------------");
                            fprintf(fp, "-+-");
                        }
                        fprintf(fp, "\n");

                        // Save the result set to the file
                        while ((row = mysql_fetch_row(res)) != NULL) {
                            for (int i = 0; i < mysql_num_fields(res); i++) {
                                fprintf(fp, "%-*s", 20, row[i]);
                                fprintf(fp, " | ");
                            }
                            fprintf(fp, "\n");
                        }


                        // Print a dividing line
                        for (int i = 0; i < mysql_num_fields(res); i++) {
                            fprintf(fp, "--------------------");
                            fprintf(fp, "-+-");
                        }
                        fprintf(fp, "\n");

                        // Close the file and the connection
                        fclose(fp);
                        mysql_free_result(res);
                        mysql_close(conn);


                        printf("\n\nVoulez vous continuer ?");
                        printf("\n1- Oui");
                        printf("\n2- Non");
                        printf("\nvotre choix : ");
                        scanf("%d", &end);
                        if(end == 2){
                            break;
                        }
                        break;

                    case 15:
                        //Doc curl

                        CURL *curl = curl_easy_init();

                        if (!curl) {
                            fprintf(stderr, "Il y a eu un probleme lors de l'initialisation de curl\n");
                            return EXIT_FAILURE;
                        }

                        curl_easy_setopt(curl, CURLOPT_URL, "http://192.168.96.138/curlfile.html");

                        CURLcode result = curl_easy_perform(curl);

                        if(result != CURLE_OK){
                            fprintf(stderr, "download problem: %s\n", curl_easy_strerror(result));
                        }

                        curl_easy_cleanup(curl);
                        return EXIT_SUCCESS;

                        printf("\n\nVoulez vous continuer ?");
                        printf("\n1- Oui");
                        printf("\n2- Non");
                        printf("\nvotre choix : ");
                        scanf("%d", &end);
                        if(end == 2){
                            break;
                        }
                        break;
                    }
                }
            }

//2
        }
    }else if(choice1 == 2){

        if(!(mysql_real_connect(conn, host, user, pass, dbname, 3306,  NULL, 0)))
        {
            fprintf(stderr, "\nError: %s [%d]\n", mysql_error(conn), mysql_errno(conn));
            exit(1);
        }
        else {printf("Connexion Reussie !\n\n");}

        //demande d'infos (BDD)
        char bdd_name[258];
        char query[258];

        printf("Veuillez saisir le nom de votre BASE : ");
        scanf("%s", &bdd_name);

        sprintf(query, "CREATE DATABASE %s", bdd_name);

        if(mysql_query(conn, query))
        {
            fprintf(stderr, "\n%s\n", mysql_error(conn));
            mysql_close(conn);
            exit(1);
        }else{printf("\n\nBDD %s créée avec succés !");}
    }

    else if(choice1 == 3){

        CURL *curl = curl_easy_init();

        if (!curl) {
            fprintf(stderr, "Il y a eu un probleme lors de l'initialisation de curl\n");
            return EXIT_FAILURE;
        }

        curl_easy_setopt(curl, CURLOPT_URL, "http://192.168.96.138/curlfile.html");

        CURLcode result = curl_easy_perform(curl);

        if(result != CURLE_OK){
            fprintf(stderr, "download problem: %s\n", curl_easy_strerror(result));
        }

        curl_easy_cleanup(curl);
        return EXIT_SUCCESS;
    }
}









































































































