#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define COURSE_SIZE 20
#define NUM_COURSES 20
#define MAX_SIZE 1024
#define MAX_SEATS 12
#define course_len 30
#define MAX_SLOT 5
#define MAX_SUB 10

typedef struct Student
{
    char name[50];
    char enrolment_number[11];
    int roll_no;
    char courses[5][50];
    int slots[5];
    int height;
    struct Student *left;
    struct Student *right;
} student;

typedef struct linkedStd
{
    char Name[50];
    int roll;
    char enrol_num[11];
    int height;
    struct linkedStd *left;
    struct linkedStd *right;
} linkedStudent;

typedef struct course
{
    char name[50];
    int slot;
    int course_id;
    int strength;
    int height;
    linkedStudent *students;
    struct course *left;
    struct course *right;
} Course;

typedef struct Classroom
{
    int class_no;
    int courseinslot[MAX_SLOT];
    int num_seats;
    int height;
    int seats[4][MAX_SEATS/3];
    struct Classroom *left;
    struct Classroom *right;
}Classroom;

typedef struct Slot
{
    int slot_no;
    int sub[MAX_SLOT];
    struct Slot *next;
}slot;

slot* init(slot* slot_name){
    printf("ed");
    slot_name->next=NULL;
    slot_name->slot_no=0;
    for(int i=0;i<5;i++){
        slot_name->sub[i]=0;
    }
    return slot_name;
}

slot* createslotlist(int Numnodes)
{
    slot* nptr=NULL;
    slot* lptr=NULL;
    int i;
    int count=1;
    for(i=1;i<=Numnodes;i++)
    {   
        printf("sd");
        nptr=(slot*)malloc(sizeof(slot));
        init(nptr);
        nptr->slot_no=count;
        nptr->next=lptr;
        lptr=nptr;
        count++;
    }
    return lptr;
}

slot* traverse(slot* slot_name,int k){
    slot* ptr=slot_name;
    slot* tptr;
    int flag=1;
    while (ptr!=NULL && flag==1)
    {
        printf("started");
        if(ptr->slot_no==k){
            tptr=ptr;
        }
        flag=0;
        ptr=ptr->next;
    }
    return tptr;
}

void InitializeCourseNode(Course *cs)
{
    strcpy(cs->name, " ");
    cs->slot = 0;
    cs->students = NULL;
    cs->strength = 0;
    cs->height=1;
    cs->left = NULL;
    cs->right = NULL;
}

void InitializeclassNode(Classroom *cs)
{
    cs->class_no=0;
    cs->height=1;
    cs->num_seats=0;
    for(int i=0;i<MAX_SLOT;i++){
        cs->courseinslot[i]=0;
    }
    for(int i=0;i<4;i++){
        for(int j=0;j<MAX_SEATS;j++){
            cs->seats[i][j]=0;
        }
    }
    cs->left = NULL;
    cs->right = NULL;
}

void initialize_HT(Course *coursearr[])
{
    int i = 0;
    for (i = 0; i < COURSE_SIZE; i++)
    {
        coursearr[i] = NULL;
        // printf("creating");
    }
}

int max(int a, int b)
{
    int ret_val;
    if (a > b)
    {
        ret_val = a;
    }
    else
    {
        ret_val = b;
    }
    return ret_val;
}

//question 1 inserting and deleting student node 644
int get_height(student *root)
{
    int ret_val = 0;
    if (root!= NULL)
    {
        ret_val = 1 + max(get_height(root->left),get_height(root->right));
    }
    return ret_val;
}

int get_balance(student *root)
{
    return (get_height(root->left) - get_height(root->right));
}

student *rotate_right(student *root)
{
    student *x = root->left;
    root->left = x->right;
    x->right = root;
    return x;
}

student *rotate_left(student *root)
{
    student *x = root->right;
    root->right = x->left;
    x->left = root;
    return x;
}
student *insert(student *root, student *nptr)
{
    int d = nptr->roll_no;
    if (root == NULL)
    {
        root = nptr;
        nptr->height = 1;
    }
    else
    {
        if (d < root->roll_no)
        {
            root->left = insert(root->left, nptr);
            root->height = get_height(root);
        }
        else
        {
            root->right = insert(root->right, nptr);
            root->height = get_height(root);
        }
    }

    int balance = get_balance(root);

    if (balance > 1 && d < root->left->roll_no)
    {
        root = rotate_right(root);
    }
    else if (balance > 1 && d > root->left->roll_no)
    {
        root->left = rotate_left(root->left);
        root = rotate_right(root);
    }
    else if (balance < -1 && d > root->right->roll_no)
    {
        root = rotate_left(root);
    }
    else if (balance < -1 && d < root->right->roll_no)
    {
        root->right = rotate_right(root->right);
        root = rotate_left(root);
    }
    return root;
}

void visit(student *root)
{
    if (root != NULL)
    {
        visit(root->left);
        printf("name-%s, roll-%d, ht :%d\n",root->name, root->roll_no, root->height);

        visit(root->right);
    }
}

student *insertfrominput(student *root)
{
    student *temp;
    temp = (student *)malloc(sizeof(student));
    temp->height = 1;
    printf("ENTER THE NAME\n");
    scanf("%s", temp->name);

    printf("ENTER THE ENROLMENT NUMBER \n");
    scanf("%s", temp->enrolment_number);

    int i = 0, j = 0;
    while (i < 5)
    {
        printf("ENTER THE COURSE \n");
        scanf("%s", temp->courses[i]);
        i++;
    }

    while (j < 5)
    {
        printf("ENTER THE SLOT \n");
        scanf("%d", &temp->slots[j]);
        j++;
    }

    printf("ENTER THE roll no \n");
    scanf("%d", &temp->roll_no);

    insert(root, temp);
    return root;
}

student *delete_node(student *root, int key)
{
    if (root == NULL)
        return root;

    if (key < root->roll_no)
        root->left = delete_node(root->left, key);
    else if (key > root->roll_no)
        root->right = delete_node(root->right, key);
    else
    {
        if (root->left == NULL && root->right == NULL)
        {
            free(root);
            root = NULL;
        }
        else if (root->left == NULL)
        {
            student *temp = root;
            root = root->right;
            free(temp);
        }
        else if (root->right == NULL)
        {
            student *temp = root;
            root = root->left;
            free(temp);
        }
        else
        {
            student *temp = root->right;
            while (temp->left != NULL)
                temp = temp->left;
            root->roll_no = temp->roll_no;
            root->right = delete_node(root->right, temp->roll_no);
        }
    }

    if (root == NULL)
        return root;

    root->height = 1 + max(get_height(root->left), get_height(root->right));

    int balance = get_balance(root);

    if (balance > 1 && get_balance(root->left) >= 0)
        return rotate_right(root);

    if (balance > 1 && get_balance(root->left) < 0)
    {
        root->left = rotate_left(root->left);
        return rotate_right(root);
    }

    if (balance < -1 && get_balance(root->right) <= 0)
        return rotate_left(root);

    if (balance < -1 && get_balance(root->right) > 0)
    {
        root->right = rotate_right(root->right);
        return rotate_left(root);
    }
    return root;
}

//inserting course node to course tree
int get_height_course(Course *root)
{
    int ret_val = 0;
    if (root!= NULL)
    {
        ret_val = 1 + max(get_height_course(root->left),get_height_course(root->right));
    }
    return ret_val;
}

int get_balance_course(Course *root)
{
    return (get_height_course(root->left) - get_height_course(root->right));
}

Course *rotate_right_course(Course *root)
{
    Course *x = root->left;
    root->left = x->right;
    x->right = root;
    return x;
}

Course *rotate_left_course(Course *root)
{
    Course *x = root->right;
    root->right = x->left;
    x->left = root;
    return x;
}
Course *insert_course(Course *root, Course *nptr)
{
    int d = nptr->course_id;
    if (root == NULL)
    {
        root = nptr;
        nptr->height = 1;
    }
    else
    {
        if (d < root->course_id)
        {
            root->left = insert_course(root->left, nptr);
            root->height = get_height_course(root);
        }
        else
        {
            root->right = insert_course(root->right, nptr);
            root->height = get_height_course(root);
        }
    }

    int balance = get_balance_course(root);

    if (balance > 1 && d < root->left->course_id)
    {
        root = rotate_right_course(root);
    }
    else if (balance > 1 && d > root->left->course_id)
    {
        root->left = rotate_left_course(root->left);
        root = rotate_right_course(root);
    }
    else if (balance < -1 && d > root->right->course_id)
    {
        root = rotate_left_course(root);
    }
    else if (balance < -1 && d < root->right->course_id)
    {
        root->right = rotate_right_course(root->right);
        root = rotate_left_course(root);
    }
    return root;
}

//creating array of course pointers and a list of subjects in a slot
slot* create_slot_subs(Course* coursearr[],slot* slot_root)
{
    printf("started");
    FILE *fp = fopen("Book2.csv", "r");
    slot* temp;
    Course *nptr;
    printf("started");
    int count = 0;
    int i = 0;
    int val;
    int flag = 1;
    if (!fp)
        printf("Can't open file\n");

    else
    {
        flag = 1;
        char buffer[MAX_SIZE];
        int key1 = 0;
        int row = 0;
        int column = 0;
        printf("inside");

        while (fgets(buffer,
                     MAX_SIZE, fp))
        {
            column = 0;
            row++;
            if (row == 1)
            {
                // skip this iteration
            }
            else
            {
                flag = 1;
                char *value = strtok(buffer, ", ");
                nptr = (Course *)malloc(sizeof(Course));
                InitializeCourseNode(nptr);

                while (value)
                {
                    if (column == 0)
                    {
                        strcpy(nptr->name, value);
                    }

                    if (column == 1)
                    {
                        nptr->slot = atoi(value);
                    }
                    if(column == 2)
                    {
                        nptr->course_id = atoi(value);
                    }
                    value = strtok(NULL, ", ");
                    column++;
                }
                printf("creates");


                temp=traverse(slot_root,nptr->slot);
                int flag=0;
                while(flag==0){
                    for(int i=0;i<MAX_SLOT;i++){
                        if(temp->sub[i]==0){
                            temp->sub[i]=nptr->course_id;
                            flag=1;
                        }
                    }
                }
                printf("traversed");

                if(coursearr[nptr->course_id]==NULL){
                    coursearr[nptr->course_id]=nptr;
                    printf("working");
                }
                else
                {
                    printf("course with same course id already exists");
                }
            }
        }

        fclose(fp);
    }
    return slot_root;
}

Course* create_course_tree(Course* course_root,Course* coursearr[]){
    // FILE *fp = fopen("Book2.csv", "r");
    // Course *nptr;

    // int i = 0;
    // int val;
    // int flag = 1;
    // if (!fp)
    //     printf("Can't open file\n");

    // else
    // {
    //     flag = 1;
    //     char buffer[MAX_SIZE];
    //     int key1 = 0;
    //     int row = 0;
    //     int column = 0;
    //     printf("creating");
    //     while (fgets(buffer,
    //                  MAX_SIZE, fp))
    //     {
    //         column = 0;
    //         row++;
            
    //             char *value = strtok(buffer, ", ");
    //             nptr = (Course *)malloc(sizeof(Course));
    //             InitializeCourseNode(nptr);

    //             while (value)
    //             {
    //                 if (column == 0)
    //                 {
    //                     strcpy(nptr->name, value);
    //                 }

    //                 if (column == 1)
    //                 {
    //                     nptr->slot = atoi(value);
    //                 }
    //                 if(column == 2)
    //                 {
    //                     nptr->course_id = atoi(value);
    //                 }
    //                 value = strtok(NULL, ", ");
    //                 column++;
    //             }
                for(int i=1;coursearr[i]!=NULL;i++){
                    course_root=insert_course(course_root,coursearr[i]);
                }
            
    //     }

    //     fclose(fp);
    // }
    return course_root;
}

Course* coursein(Course* course_root){
    FILE *fp = fopen("Book2.csv", "r");
    Course *nptr;

    int i = 0;
    int val;
    int flag = 1;
    if (!fp)
        printf("Can't open file\n");

    else
    {
        flag = 1;
        char buffer[MAX_SIZE];
        int key1 = 0;
        int row = 0;
        int column = 0;
        printf("creating");
        while (fgets(buffer,
                     MAX_SIZE, fp))
        {
            column = 0;
            row++;
            
                char *value = strtok(buffer, ", ");
                nptr = (Course *)malloc(sizeof(Course));
                InitializeCourseNode(nptr);

                while (value)
                {
                    if (column == 0)
                    {
                        strcpy(nptr->name, value);
                    }

                    if (column == 1)
                    {
                        nptr->slot = atoi(value);
                    }
                    if(column == 2)
                    {
                        nptr->course_id = atoi(value);
                    }
                    value = strtok(NULL, ", ");
                    column++;
                }
                course_root=insert_course(course_root,nptr);
            
        }

        fclose(fp);
    }
    return course_root;
}

//adding students to their taken courses 
int get_height_linkstd(linkedStudent *root)
{
    int ret_val = 0;
    if (root != NULL)
    {
        ret_val =1 + max(get_height_linkstd(root->left),get_height_linkstd(root->right));
    }
    return ret_val;
}

int get_balance_linkstd(linkedStudent *root)
{
    return (get_height_linkstd(root->left) - get_height_linkstd(root->right));
}

linkedStudent *rotate_right_linkstd(linkedStudent *root)
{
    linkedStudent *x = root->left;
    root->left = x->right;
    x->right = root;
    return x;
}

linkedStudent *rotate_left_linkstd(linkedStudent *root)
{
    linkedStudent *x = root->right;
    root->right = x->left;
    x->left = root;
    return x;
}
linkedStudent *insert_linkstd(linkedStudent *root, linkedStudent *nptr)
{
    printf("entered \n");
    // linkedStudent *nptr = (linkedStudent *)malloc(sizeof(linkedStudent));
    // strcpy(nptr->Name, sptr->name);
    // strcpy(nptr->enrol_num, sptr->enrolment_number);
    // nptr->roll = sptr->roll_no;
    int d = nptr->roll;
    if (root == NULL)
    {
        root = nptr;
        nptr->height = 1;
    }
    else
    {
        if (d < root->roll)
        {
            root->left = insert_linkstd(root->left, nptr);
            root->height = get_height_linkstd(root);
        }
        else
        {
            root->right = insert_linkstd(root->right, nptr);
            root->height = get_height_linkstd(root);
        }
    }

    int balance = get_balance_linkstd(root);

    if (balance > 1 && d < root->left->roll)
    {
        root = rotate_right_linkstd(root);
    }
    else if (balance > 1 && d > root->left->roll)
    {
        root->left = rotate_left_linkstd(root->left);
        root = rotate_right_linkstd(root);
    }
    else if (balance < -1 && d > root->right->roll)
    {
        root = rotate_left_linkstd(root);
    }
    else if (balance < -1 && d < root->right->roll)
    {
        root->right = rotate_right_linkstd(root->right);
        root = rotate_left_linkstd(root);
    }
    return root;
}

student *insert_SR(student *student_root, Course* coursearr[])
{
    FILE *fp = fopen("Book1.csv", "r");
    // Student* stud_std=*scholar;
    // Student* prev=NULL;
    // Student* ptr;
    // printf("1\n");
    int i, j;
    int val;
    int flag = 1;
    if (!fp)
        printf("Can't open file\n");

    else
    {
        flag = 1;
        char buffer[MAX_SIZE];
        int key1 = 0;
        int row = 0;
        int column = 0;

        while (fgets(buffer, MAX_SIZE, fp))
        {
            student *std;
            std = (student *)malloc(sizeof(student));
            linkedStudent* linkstud;
            linkstud = (linkedStudent *)malloc(sizeof(linkedStudent));
            if(linkstud == NULL){
                printf("can't");
            }
            // initialize_student_node(std);
            std->height = 1;
            linkstud->height=1;
            column = 0;
            row++;
            if (row == 1)
            {
                // skip this iteration
            }
            else
            {
                flag = 1;
                char *value = strtok(buffer, ", ");

                while (value)
                {

                    if (column == 0)
                    {
                        strcpy(std->name, value);
                        strcpy(linkstud->Name, value);
                    }

                    if (column == 1)
                    {
                        strcpy(std->enrolment_number, value);
                        strcpy(linkstud->enrol_num,value);
                    }

                    if (column == 2)
                    {
                        strcpy(std->courses[0], value);
                    }

                    if (column == 3)
                    {
                        std->slots[0] = atoi(value);
                    }

                    if (column == 4)
                    {
                        strcpy(std->courses[1], value);
                    }

                    if (column == 5)
                    {
                        std->slots[1] = atoi(value);
                    }

                    if (column == 6)
                    {
                        strcpy(std->courses[2], value);
                    }

                    if (column == 7)
                    {
                        std->slots[2] = atoi(value);
                    }

                    if (column == 8)
                    {
                        strcpy(std->courses[3], value);
                    }

                    if (column == 9)
                    {
                        std->slots[3] = atoi(value);
                    }

                    if (column == 10)
                    {
                        strcpy(std->courses[4], value);
                    }

                    if (column == 11)
                    {
                        std->slots[4] = atoi(value);
                    }

                    if (column == 12)
                    {
                        std->roll_no = atoi(value);
                        linkstud->roll = atoi(value);
                    }
                    value = strtok(NULL, ", ");
                    column++;
                }
                // printf("%d \n",std->roll_no);
                 for(i=0; i<5 && flag==1;i++)
                {
                	for(j=i+1;j<5 && flag==1;j++)
                    {
                        if(std->slots[i]==std->slots[j])
                        {
                            flag=0;
                        }
                    }
                }

                if(flag!=0)
                {
                student_root = insert(student_root, std);
                 }

                // for(int i=0;i<5;i++){
                //     for(int j=1;j<10;j++){
                //         if(strcmp(coursearr[j]->name,std->courses[i])==0){
                //             (coursearr[j]->strength)++;
                //             coursearr[j]->students=insert_linkstd(coursearr[j]->students,linkstud);
                //             flag=0;
                //         }
                //     }
                // }
                // printf("%s\n",coursearr[]);
            }
        }
        fclose(fp);
    }
    return student_root;
}


void visitcourse(linkedStudent *root)
{
    visitcourse(root->left);
    printf("%d, ht :%d\n", root->roll, root->height);
    visitcourse(root->right);
}

void printcourse(Course* coursearr[])
{
    int i = 0, count = 0;
    while (i < COURSE_SIZE){
        if (coursearr[i] != NULL){
            printf("course: %s", coursearr[i]->name);
            visitcourse(coursearr[i]->students);
        }
        i++;
    }
}

//creating classroom tree
int get_height_class(Classroom *root)
{
    int ret_val = 0;
    if (root != NULL)
    {
        ret_val = 1 + max(get_height_class(root->left), get_height_class(root->right));
    }
    return ret_val;
}

int get_balance_class(Classroom *root)
{
    return (get_height_class(root->left) - get_height_class(root->right));
}

Classroom *rotate_right_class(Classroom *root)
{
    Classroom *x = root->left;
    root->left = x->right;
    x->right = root;
    return x;
}

Classroom *rotate_left_class(Classroom *root)
{
    Classroom *x = root->right;
    root->right = x->left;
    x->left = root;
    return x;
}
Classroom *insert_class(Classroom *root, Classroom *nptr)
{
    int d = nptr->class_no;
    if (root == NULL)
    {
        root = nptr;
        nptr->height = 1;
    }
    else
    {
        if (d < root->class_no)
        {
            root->left = insert_class(root->left, nptr);
            root->height = get_height_class(root);
        }
        else
        {
            root->right = insert_class(root->right, nptr);
            root->height = get_height_class(root);
        }
    }

    int balance = get_balance_class(root);

    if (balance > 1 && d < root->left->class_no)
    {
        root = rotate_right_class(root);
    }
    else if (balance > 1 && d > root->left->class_no)
    {
        root->left = rotate_left_class(root->left);
        root = rotate_right_class(root);
    }
    else if (balance < -1 && d > root->right->class_no)
    {
        root = rotate_left_class(root);
    }
    else if (balance < -1 && d < root->right->class_no)
    {
        root->right = rotate_right_class(root->right);
        root = rotate_left_class(root);
    }
    return root;
}

Classroom* insert_classroom_input(Classroom * class){
    FILE* fp = fopen("Book3.csv", "r");
      
      Classroom* nptr;
    //   Course* lptr=NULL;
    //   Course* ptr;
      
      int count=0;
      int i=0;
      int val;
      int flag=1;
    if (!fp)
        printf("Can't open file\n");
 
    else {
        flag=1;
        char buffer[MAX_SIZE];
        int key1=0;
        int row = 0;
        int column = 0;
 
        while (fgets(buffer,
                     MAX_SIZE, fp)) {
            column = 0;
            row++;
          if(row==1)
          {
            //skip this iteration
          }
          else
          {
            flag=1;
            char* value = strtok(buffer, ", ");
            nptr=(Classroom*)malloc(sizeof(Classroom));
            InitializeclassNode(nptr);

            while (value ) {
                
                if (column == 0) {
                   nptr->class_no=atoi(value);
                   
                }
 
                if (column == 1) {
                    nptr->num_seats=atoi(value);
                }
 
               
                value = strtok(NULL, ", ");
                column++;
            }
            class=insert_class(class,nptr);
        }
    }
    }
    return class;
}

Classroom* visit_class(Classroom *root,int k)
{
    if (root != NULL)
    {
        visit_class(root->left,k);
        if(root->num_seats<=k){
            return root;
        }

        visit_class(root->right,k);
    }
    return root;
}

//allotment of classrooms
Classroom* allotment_of_classrooms(Classroom* classroom_root,slot* slot_root,Course* coursearr[]){
    slot* ptr;
    Classroom* class1;
    for(int i=1;coursearr[i]!=NULL;i++){
        while(ptr!=NULL){
            int slot1=ptr->slot_no;
            class1=visit_class(classroom_root,coursearr[i]->strength);
            class1->courseinslot[slot1-1]=coursearr[i]->course_id;
            ptr=ptr->next;
        }
    }
    return classroom_root;
}

Classroom* traverse_in_class(Classroom* root){
    if (root != NULL)
    {
        traverse_in_class(root->left);
        return root;
        traverse_in_class(root->right);
    }
    return root;
}

linkedStudent* traverse_in_studcourse(linkedStudent* root){
    if (root != NULL)
    {
        traverse_in_studcourse(root->left);
        return root;
        traverse_in_studcourse(root->right);
    }
    return root;
}


//allotment of exam seating
Classroom* allotment_of_exams(Classroom* classroom_root,Course* coursearr[]){
    Classroom* class1=classroom_root;
    linkedStudent* stud;
    for(int i=1;coursearr[i]!=NULL;i++){
        int k=coursearr[i]->strength;
        stud=coursearr[i]->students;
        while(k>0){
            int p=class1->num_seats;
            while(p>0){
            for(int i=0;i<4;i++){
                for(int j=0;j<MAX_SEATS;j=j+3){
                    if(j==0){
                    if(class1->seats[i][j]!=0){
                        j++;
                        if(class1->seats[i][j+1]!=0){
                            j++;
                        }
                    }
                    }
                    class1->seats[i][j]=stud->roll;
                    printf("details of student in seat no (%d,%d) in class-%d are\n",i,j,class1->class_no);
                    printf("Name: %s\nenrol_n0: %s\n",stud->Name,stud->enrol_num);
                }
                stud=traverse_in_studcourse(stud);
                k--;
            }
            class1=traverse_in_class(class1);
            }
        }
    }
    return classroom_root;
}

//rangesearch
void rangeSearch( Course* root, int low, int high) {
    if (root == NULL) return;
    if(root->course_id<low)
    {
        rangeSearch(root->right,low,high);
    }
    else if (root->course_id > low)
    {
        rangeSearch(root->left, low, high);
    }

    if (root->course_id > low && root->course_id < high) {
        printf("%d ", root->course_id);
    }

    if (root->course_id > high)
        rangeSearch(root->left,low,high);
    else if (root->course_id < high)
        rangeSearch(root->right, low, high);
}


int main()
{
    int key;

    student *student_root = NULL;
    Classroom* classroom_root = NULL;
    Course * coursearr[COURSE_SIZE];
    slot* slot_root;
    Course* course_root;
    Course* course1;
    initialize_HT(coursearr);
    int question;
    printf("enter the question no");
    scanf("%d",&question);
    switch (question)
    {
    case 1://1 & 2
        student_root = insert_SR(student_root,coursearr);
        visit(student_root);
        int key;
        printf("enter the node to be deleted \n");
        scanf("%d", &key);
        student_root = delete_node(student_root,key);
        visit(student_root);
        // student_root=insertfrominput(student_root);
        break;
    case 3:
        course_root=create_course_tree(course_root,coursearr);
        printf("%d",course_root->course_id);
        break;
    case 4:
        slot_root=createslotlist(5);
        slot_root=create_slot_subs(coursearr,slot_root);
        classroom_root=insert_classroom_input(classroom_root);
        classroom_root=allotment_of_classrooms(classroom_root,slot_root,coursearr);
        break;
    case 5:
        classroom_root=allotment_of_exams(classroom_root,coursearr);
        break;
    case 7:
        course1=coursein(course1);
        printf("enter low and high");
        int low,high;
        scanf("%d %d",&low,&high);
        rangeSearch(course1,low,high);
    default:
        break;
    }
    return 0;
}
