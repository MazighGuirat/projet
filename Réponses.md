// Guirat Mazigh G01
// Projet de SE TP 

Réponses aux questions :

Q1: Quelles sont les structures de données à utiliser ?

1\ Matrices B, C et A : Ces matrices doivent être des tableaux bidimensionnels, comme déclaré dans le code ('int B[N][N]',' int C[N][N]', 'int A[N][N]').

2\ Matrice Tampon T : La matrice tampon T doit également être un tableau bidimensionnel, comme déclaré dans le code ('int T[N][N];'). C'est dans cette matrice que les résultats intermédiaires seront stockés.

Q2: Comment allez-vous protéger l'accès à ces données?

1\ Sémaphores et Mutex : Dans le code, les sémaphores ('empty' et 'full') et le mutex sont utilisés pour synchroniser l'accès aux données partagées.

a\ 'sem_wait(&empty)' : est utilisé pour garantir qu'il y a de la place dans le tampon avant d'écrire.

b\ 'sem_post(&empty)' : est utilisé pour signaler qu'une place est libérée après l'écriture.

c\ 'sem_wait(&full)' : est utilisé pour attendre qu'il y ait des données à lire dans le tampon.

d\ 'sem_post(&full)' : est utilisé pour signaler que des données ont été consommées du tampon.

e\ 'pthread_mutex_lock(&mutex)' : est utilisé avant d'écrire ou de lire dans le tampon, pour éviter les conflits d'accès concurrents.

f\ 'pthread_mutex_unlock(&mutex)' : est utilisé pour libérer le mutex après l'écriture ou la lecture.

Q3: Quels sont les risques?

1\ Condition de concurrence : Il y a un risque de condition de concurrence si l'accès aux données partagées n'est pas correctement synchronisé. Cela pourrait conduire à des résultats incorrects dans la matrice résultante A.

2\ Blocage : Il y a un risque de blocage si la synchronisation n'est pas correctement gérée. Par exemple, si un producteur attend indéfiniment une place libre dans le tampon qui ne vient jamais, ou si un consommateur attend indéfiniment des données dans un tampon vide.

3\ Erreur de segmentation : Il peut y avoir des erreurs de segmentation si les indices d'accès aux tableaux ne sont pas correctement gérés, dépassant les limites des tableaux.

4\ Performances : La parallélisation peut ne pas apporter de bénéfices significatifs si la taille des matrices est petite. Il est important de mesurer les performances et de déterminer si la parallélisation est justifiée pour la taille des données en question.

5\ Gestion des erreurs : Le code ne gère pas actuellement les erreurs qui pourraient survenir pendant l'exécution (par exemple, l'échec de la création d'un thread). Une gestion des erreurs robuste devrait être ajoutée pour assurer une exécution fiable du programme.
