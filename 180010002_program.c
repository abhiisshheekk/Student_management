#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

enum branch {CSE, EE, ME};

struct course {
    char code[MAX];
    char name[MAX];
    int credits;
    int ninstructors;
    char **instructor_ids;
    int nstudents;
    char **student_rollnos;
};

struct student {
    char rollno[MAX];
    char name[MAX];
    enum branch branch;
    int semester;
    int ncourses;
    char **course_codes;
};

struct instructor {
    char id[MAX];
    char name[MAX];
    int ncourses;
    char **courses_codes;
};

void print_students();
void print_instructors();
void print_courses();

void print_student(struct student s);
void print_instructor(struct instructor in);
void print_course(struct course c);

void add_student(struct student s);
void add_instructor(struct instructor in);
void add_course(struct course c);

void load_records();
void load_students();
void load_instructors();
void load_courses();

void new_course();
void new_student();
void new_instructor();

void default_course_roll(char *crcode,char *roll);
void default_course_id(char *crcode,char *inid);
void default_student (char *roleno,char *ccode);
void default_instructor(char *identity,char *code);

void delete_student();
void delete_instructor();
void delete_course();

void fprintf_course();
void fprintf_student();
void fprintf_instructor();

void modify_student();
void modify_instructor();
void modify_course();

struct course *courses;
struct student *students;
struct instructor *instructors;

FILE *fps;
FILE *fpc;
FILE *fpi;

char students_file[MAX] = "students.txt";
char courses_file[MAX] = "courses.txt";
char instructors_file[MAX] = "instructors.txt";

int ncourses = 0, nstudents = 0, ninstructors = 0;

int main() {
    load_records();
	int opt,sel;
	printf("\t\t\t\tCourse Management:-\n\n");
	printf("Choose one of the following options:\n\n1.Students Information\n2.Instructors Information\n3.Courses Information\n4.Exit\n\n>>>");
	while(1){
		scanf("%d",&opt);
		switch(opt){
			case 1 : printf("Student Options:\n\nChoose What you want to do? :\n\n1.Display all students information\n2.Display a particular student's information\n3.Add a new student's information\n4.Delete a particular student's information\n5.Modify a particular student's information\n6.Go Back\n7.Exit\n\n>>>");
					 scanf("%d",&sel);
					 switch(sel){
					 	 case 1 : printf("\n");
					 	 		  print_students();
					 	 		  break;
                         case 2 : printf("\nEnter Roll no. of the Student: ");
                                  char search[MAX];
                                  scanf("%s", search);
                                  int i=0;
                                  while (i != nstudents) {
                                      if(strcmp(search,students[i].rollno) == 0) {
                                          printf("\nStudent's Information:-\n\n");
                                          print_student(students[i]);
                                          break;
                                      }
                                      i++;
                                  }
                                  if(i == nstudents) printf("\nInvalid input!\n");
                                  break;
                         case 3 : printf("Enter the following details of the new Student:-\n\n");
                                  new_student();
                                  printf("\n*Student added\n");
                                  break;
                         case 4 : delete_student();
                                  printf("\n*Student deleted\n");
                                  break;
                         case 5 : modify_student();
                                  printf("\n*Student details updated\n");
                                  break;
                         case 6 : printf("\n----------------------------------------------\nChoose one of the following options:\n\n1.Students Information\n2.Instructors Information\n3.Courses Information\n4.Exit\n\n>>>");
                                  continue;
                        default : return 0;
					 }
					 break;
			case 2 : printf("Instructor Options:\n\nChoose What you want to do? :\n\n1.Display all instructors information\n2.Display a particular instructor's information\n3.Add a new instructor's information\n4.Delete a particular instructor's information\n5.Modify a particular instructor's information\n6.Go Back\n7.Exit\n\n>>>");
					 scanf("%d",&sel);
					 switch(sel){
					 	 case 1 : printf("\n");
					 	 		  print_instructors();
					 	 		  break;
                         case 2 : printf("\nEnter the Instructor ID: ");
                                  char search[MAX];
                                  scanf("%s", search);
                                  int i=0;
                                  while (i != ninstructors) {
                                      if(strcmp(search,instructors[i].id) == 0) {
                                          printf("\nInstructor's Information:-\n\n");
                                          print_instructor(instructors[i]);
                                          break;
                                      }
                                      i++;
                                  }
                                  if(i == ninstructors) printf("\nInvalid input!\n");
                                  break;
                         case 3 : printf("Enter the following details of the new instructor:-\n\n");
                                  new_instructor();
                                  printf("\n*Instructor added\n");
                                  break;
                         case 4 : delete_instructor();
                                  printf("\n*Instructor deleted\n");
                                  break;
                         case 5 : modify_instructor();
                                  printf("\n*Instructor's details updated\n");
                                  break;
                         case 6 : printf("\n----------------------------------------------\nChoose one of the following options:\n\n1.Students Information\n2.Instructors Information\n3.Courses Information\n4.Exit\n\n>>>");
                                  continue;
                        default : return 0;
					 }
					 break;
			case 3 : printf("Course Options:\n\nChoose What you want to do? :\n\n1.Display all courses information\n2.Display a particular course's information\n3.Add a new course's information\n4.Delete a particular course's information\n5.Modify a particular course's information\n6.Go Back\n7.Exit\n\n>>>");
					 scanf("%d",&sel);
					 switch(sel){
					 	 case 1 : printf("\n");
                                  print_courses();
					 	 		  break;
                         case 2 : printf("\nEnter the Course code: ");
                                  char search[MAX];
                                  scanf("%s", search);
                                  int i=0;
                                  while (i != ncourses) {
                                      if(strcmp(search,courses[i].code) == 0) {
                                          printf("\nCourse's Information:-\n\n");
                                          print_course(courses[i]);
                                          break;
                                      }
                                      i++;
                                  }
                                  if(i == ncourses) printf("\nInvalid input!\n");
                                  break;
                         case 3 : printf("Enter the following details of the new course:-\n\n");
                                  new_course();
                                  printf("\n*Course added\n");
                                  break;
                         case 4 : delete_course();
                                  printf("\n*Course deleted\n");
                                  break;
                         case 5 : modify_course();
                                  printf("\n*Course details updated\n");
                                  break;
                         case 6 : printf("\n----------------------------------------------\nChoose one of the following options:\n\n1.Students Information\n2.Instructors Information\n3.Courses Information\n4.Exit\n\n>>>");
                                  continue;
                        default : return 0;
					 }
					 break;
            case 4 : return 0;
			default: printf("\nPlease select one of the above options:\n\n>>>");
					 continue;
		}
		break;
	}
    return 0;
}

void add_student(struct student s) {
    students = realloc (students, (nstudents+1)*sizeof(struct student));
    students[nstudents] = s;
    nstudents++;
}

void add_instructor(struct instructor in) {
	instructors = realloc (instructors, (ninstructors+1)*sizeof(struct instructor));
	instructors[ninstructors] = in;
	ninstructors++;
}

void add_course(struct course c) {
    courses = realloc (courses, (ncourses+1)*sizeof(struct course));
    courses[ncourses] = c;
    ncourses++;
}

void new_student() {
    struct student st;
    int i=0;
    printf("Student Roll no: ");
    scanf("%s",st.rollno);
    while(i != nstudents) {
        if(strcmp(st.rollno,students[i].rollno) == 0){
            printf("Student Data already exists...\n");
            break;
        }
        i++;
    }
    if (i==nstudents) {
        printf("Student Name: ");
        scanf(" %[^\n]s",st.name);
        printf("Branch(Enter integer 0:CSE,1:EE,2:ME): ");
        scanf("%u",&st.branch);
        printf("Semester: ");
        scanf("%d",&st.semester);
        printf("No. of courses: ");
        scanf("%d",&st.ncourses);
        printf("Enter Course codes(Press Enter after every course code): ");
        st.course_codes = malloc (st.ncourses * sizeof(char *));
        for(int j=0;j<st.ncourses;j++) {
            st.course_codes[j] = malloc (MAX * sizeof(char));
            scanf("%s",st.course_codes[j]);
            int k;
            for(k=0;k<ncourses;k++){
                if(strcmp(st.course_codes[j],courses[k].code) == 0){
                    courses[k].nstudents++;
                    courses[k].student_rollnos = realloc(courses[k].student_rollnos, (courses[k].nstudents) * sizeof(char *));
                    courses[k].student_rollnos[(courses[k].nstudents)-1] = malloc (MAX * sizeof(char));
                    strcpy(courses[k].student_rollnos[(courses[k].nstudents)-1], st.rollno);
                    break;
                }
            }
            if(k == ncourses) {
                default_course_roll(st.course_codes[j],st.rollno);
                printf("\n*Default course information has been given to this course. You need to update this course Information afterwards\n");
                break;
            }
        }
        add_student(st);
        fprintf_student();
        fprintf_course();
    }
}

void new_instructor() {
    struct instructor ir;
    int i=0;
    printf("Instructor ID: ");
    scanf("%s",ir.id);
    while(i != ninstructors) {
        if(strcmp(ir.id,instructors[i].id) == 0){
            printf("Instructor Data already exists...\n");
            break;
        }
        i++;
    }
    if (i==ninstructors) {
        printf("Instructor Name: ");
        scanf(" %[^\n]s",ir.name);
        printf("No. of courses: ");
        scanf("%d",&ir.ncourses);
        printf("Enter Course codes(Press Enter after every course code): ");
        ir.courses_codes = malloc (ir.ncourses * sizeof(char *));
        for(int j=0;j<ir.ncourses;j++) {
            ir.courses_codes[j] = malloc (MAX * sizeof(char));
            scanf("%s",ir.courses_codes[j]);
            int k;
            for(k=0;k<ncourses;k++){
                if(strcmp(ir.courses_codes[j],courses[k].code) == 0){
                    courses[k].ninstructors++;
                    courses[k].instructor_ids = realloc(courses[k].instructor_ids, (courses[k].ninstructors) * sizeof(char *));
                    courses[k].instructor_ids[(courses[k].ninstructors)-1] = malloc (MAX * sizeof(char));
                    strcpy(courses[k].instructor_ids[(courses[k].ninstructors)-1], ir.id);
                    break;
                }
            }
            if(k == ncourses) {
                default_course_id(ir.courses_codes[j],ir.id);
                printf("\n*Default course information has been given to this course. You need to update this course Information afterwards\n");
                break;
            }
        }
        add_instructor(ir);
        fprintf_course();
        fprintf_instructor();
    }
}

void new_course() {
    struct course co;
    int i=0;
    printf("Course code: ");
    scanf("%s",co.code);
    while(i != ncourses) {
        if(strcmp(co.code,courses[i].code) == 0){
            printf("Course already exists...\n");
            break;
        }
        i++;
    }
    if (i==ncourses) {
        printf("Course Name: ");
        scanf(" %[^\n]s",co.name);
        printf("No. of credits: ");
        scanf("%d",&co.credits);
        printf("No. of instructors: ");
        scanf("%d",&co.ninstructors);
        printf("Enter Instructor IDs(Press Enter after every instructor id): ");
        co.instructor_ids = malloc (co.ninstructors * sizeof(char *));
        for(int j=0;j<co.ninstructors;j++) {
            co.instructor_ids[j] = malloc (MAX * sizeof(char));
            scanf("%s",co.instructor_ids[j]);
            int k;
            for(k=0;k<ninstructors;k++){
                if(strcmp(co.instructor_ids[j],instructors[k].id) == 0){
                    instructors[k].ncourses++;
                    instructors[k].courses_codes = realloc (instructors[k].courses_codes, instructors[k].ncourses * sizeof(char *));
                    instructors[k].courses_codes[instructors[k].ncourses-1] = malloc (MAX * sizeof(char));
                    strcpy(instructors[k].courses_codes[instructors[k].ncourses-1],co.code);
                    break;
                }
            }
            if(k == ninstructors) {
                default_instructor(co.instructor_ids[j],co.code);
                printf("\n*Default information about this instructor has been given. You need to update this instructor's information afterwards\n");
            }
        }
        printf("No. of Students: ");
        scanf("%d",&co.nstudents);
        printf("Student Roll nos(Press Enter after every student's rollno): ");
        co.student_rollnos = malloc (co.nstudents * sizeof(char *));
        for(int j=0;j<co.nstudents;j++) {
            co.student_rollnos[j] = malloc (MAX * sizeof(char));
            scanf("%s",co.student_rollnos[j]);
            int k;
            for(k=0;k<nstudents;k++){
                if(strcmp(co.student_rollnos[j],students[k].rollno) == 0){
                    students[k].ncourses++;
                    students[k].course_codes = realloc (students[k].course_codes, students[k].ncourses * sizeof(char *));
                    students[k].course_codes[students[k].ncourses-1] = malloc (MAX * sizeof(char));
                    strcpy(students[k].course_codes[students[k].ncourses-1],co.code);
                    break;
                }
            }
            if(k == nstudents) {
                default_student(co.student_rollnos[j],co.code);
                printf("\n*Default information about this student has been given. You need to update this student's information afterwards\n");
            }
        }
        add_course(co);
        fprintf_student();
        fprintf_instructor();
        fprintf_course();
    }
}

void default_course_roll(char *crcode,char *roll) {
    struct course c;
    strcpy(c.code ,crcode);
    strcpy(c.name ,"Defense Against Dark Arts");
    c.credits = 6;
    c.ninstructors = 1;
    c.instructor_ids = malloc (c.ninstructors * sizeof(char *));
    c.instructor_ids[0] = malloc (MAX * sizeof(char));
    strcpy(c.instructor_ids[0] ,"Fill");
    c.nstudents = 1;
    c.student_rollnos = malloc (c.nstudents * sizeof(char *));
    c.student_rollnos[0] = malloc (MAX * sizeof(char));
    strcpy(c.student_rollnos[0] ,roll);
    add_course(c);
    fprintf_course();
}

void default_course_id(char *crcode,char *inid) {
    struct course c;
    strcpy(c.code ,crcode);
    strcpy(c.name ,"Defense Against Dark Arts");
    c.credits = 6;
    c.ninstructors = 1;
    c.instructor_ids = malloc (c.ninstructors * sizeof(char *));
    c.instructor_ids[0] = malloc (MAX * sizeof(char));
    strcpy(c.instructor_ids[0] ,inid);
    c.nstudents = 1;
    c.student_rollnos = malloc (c.nstudents * sizeof(char *));
    c.student_rollnos[0] = malloc (MAX * sizeof(char));
    strcpy(c.student_rollnos[0] ,"Fill");
    add_course(c);
    fprintf_course();
}

void default_student (char *roleno,char *ccode) {
    struct student s;
    strcpy(s.rollno ,roleno);
    strcpy(s.name ,"Harry Potter");
    s.branch = 0;
    s.semester = 1;
    s.ncourses = 1;
    s.course_codes = malloc (s.ncourses * sizeof(char *));
    s.course_codes[0] = malloc (MAX * sizeof(char));
    strcpy(s.course_codes[0] ,ccode);
    add_student(s);
    fprintf_student();
}

void default_instructor(char *identity,char *code) {
    struct instructor in;
    strcpy(in.id ,identity);
    strcpy(in.name ,"Albus Dumbledore");
    in.ncourses = 1;
    in.courses_codes = malloc (in.ncourses * sizeof(char *));
    in.courses_codes[0] = malloc (MAX * sizeof(char));
    strcpy(in.courses_codes[0] ,code);
    add_instructor(in);
    fprintf_instructor();
}

void delete_student() {
    char del[MAX];
    int i;
    printf("Enter the roll no of the student(whose information you want to delete): ");
    scanf("%s",del);
    for(i=0;i<nstudents;i++){
        if(strcmp(del,students[i].rollno) == 0) {
            break;
        }
    }
    if(i == nstudents) {
        printf("Student not found!");
    }
    else{
        for(int j=0;j<students[i].ncourses;j++) {
            int k,l;
            for(k=0;k<ncourses;k++) {
                if(strcmp(students[i].course_codes[j],courses[k].code) == 0) {
                    break;
                }
            }
            for(l=0;l<courses[k].nstudents;l++) {
                if(strcmp(students[i].rollno,courses[k].student_rollnos[l]) == 0) {
                    for(int a=l;a<courses[k].nstudents;a++) {
                        courses[k].student_rollnos[a] = courses[k].student_rollnos[a+1];
                    }
                    courses[k].nstudents--;
                }
            }
        }
        fprintf_course();
        for(int j=i;j<nstudents;j++){
            students[j] = students[j+1];
        }
        nstudents--;
        fprintf_student();
    }
}

void delete_instructor() {
    char del[MAX];
    int i;
    printf("Enter the Instructor ID of the instructor(whose information you want to delete): ");
    scanf("%s",del);
    for(i=0;i<ninstructors;i++){
        if(strcmp(del,instructors[i].id) == 0) {
            break;
        }
    }
    if(i == ninstructors) {
        printf("Instructor not found!");
    }
    else{
        for(int j=0;j<instructors[i].ncourses;j++) {
            int k,l;
            for(k=0;k<ncourses;k++) {
                if(strcmp(instructors[i].courses_codes[j],courses[k].code) == 0) {
                    break;
                }
            }
            for(l=0;l<courses[k].ninstructors;l++) {
                if(strcmp(instructors[i].id,courses[k].instructor_ids[l]) == 0) {
                    for(int a=l;a<courses[k].ninstructors;a++) {
                        courses[k].instructor_ids[a] = courses[k].instructor_ids[a+1];
                    }
                    courses[k].ninstructors--;
                }
            }
        }
        fprintf_course();
        for(int j=i;j<ninstructors;j++){
            instructors[j] = instructors[j+1];
        }
        ninstructors--;
        fprintf_instructor();
    }
}

void delete_course() {
    char del[MAX];
    int i;
    printf("Enter the course code of the course(whose information you want to delete): ");
    scanf("%s",del);
    for(i=0;i<ncourses;i++){
        if(strcmp(del,courses[i].code) == 0) {
            break;
        }
    }
    if(i == ncourses) {
        printf("course not found!");
    }
    else {
        for(int j=0;j<ninstructors;j++) {
            int l,k;
            for(k=0;k<instructors[j].ncourses;k++) {
                if(strcmp(instructors[j].courses_codes[k],courses[i].code) == 0) {
                    break;
                }
            }
            if(k!=instructors[j].ncourses){
                for(l=k;l<instructors[j].ncourses;l++) {
                    instructors[j].courses_codes[l] = instructors[j].courses_codes[l+1];
                }
                instructors[j].ncourses--;
            }
        }
        for(int j=0;j<nstudents;j++) {
            int l,k;
            for(k=0;k<students[j].ncourses;k++) {
                if(strcmp(students[j].course_codes[k],courses[i].code) == 0) {
                    break;
                }
            }
            if(k!=students[j].ncourses){
                for(l=k;l<students[j].ncourses;l++) {
                    students[j].course_codes[l] = students[j].course_codes[l+1];
                }
                students[j].ncourses--;
            }
        }
        for(int j=i;j<ncourses;j++){
            courses[j] = courses[j+1];
        }
        ncourses--;
        fprintf_student();
        fprintf_instructor();
        fprintf_course();
    }
}

void fprintf_course() {
    fpc = fopen(courses_file,"w");
    fprintf(fpc,"%d\n\n",ncourses);
    for(int i=0;i<ncourses;i++) {
        fprintf(fpc,"%s\n",courses[i].code);
        fprintf(fpc,"%s\n",courses[i].name);
        fprintf(fpc,"%d\n",courses[i].credits);
        fprintf(fpc,"%d\n",courses[i].ninstructors);
        for (int j=0;j<courses[i].ninstructors;j++) {
            fprintf(fpc,"%s\n",courses[i].instructor_ids[j]);
        }
        fprintf(fpc,"%d\n",courses[i].nstudents);
        for (int j=0;j<courses[i].nstudents;j++) {
            fprintf(fpc,"%s ",courses[i].student_rollnos[j]);
        }
        fprintf(fpc,"\n\n");
    }
    fclose(fpc);
}

void fprintf_student() {
    fps = fopen(students_file,"w");
    fprintf(fpc,"%d\n\n",nstudents);
    for(int i=0;i<nstudents;i++) {
        fprintf(fpc,"%s\n",students[i].rollno);
        fprintf(fpc,"%s\n",students[i].name);
        fprintf(fpc,"%d\n",students[i].branch);
        fprintf(fpc,"%d\n",students[i].semester);
        fprintf(fpc,"%d\n",students[i].ncourses);
        for (int j=0;j<students[i].ncourses;j++) {
            fprintf(fpc,"%s ",students[i].course_codes[j]);
        }
        fprintf(fpc,"\n\n");
    }
    fclose(fps);
}

void fprintf_instructor() {
    fpi = fopen(instructors_file,"w");
    fprintf(fpc,"%d\n\n",ninstructors);
    for(int i=0;i<ninstructors;i++) {
        fprintf(fpc,"%s\n",instructors[i].id);
        fprintf(fpc,"%s\n",instructors[i].name);
        fprintf(fpc,"%d\n",instructors[i].ncourses);
        for (int j=0;j<instructors[i].ncourses;j++) {
            fprintf(fpc,"%s ",instructors[i].courses_codes[j]);
        }
        fprintf(fpc,"\n\n");
    }
    fclose(fpi);
}

void print_students() {
    printf("Students' details\n-----------------\n");
    for (int i=0; i<nstudents; i++) {
    	printf("Student %d Details:-\n", i+1);
        print_student(students[i]);
    }
}

void print_instructors() {
    printf("Instructors' details\n-----------------\n");
    for (int i=0; i<ninstructors; i++) {
    	printf("Instructor %d Details:-\n", i+1);
        print_instructor(instructors[i]);
    }
}

void print_courses() {
    printf("Courses' details\n-----------------\n");
    for (int i=0;i<ncourses;i++) {
        printf("Course %d Details:-\n", i+1);
        print_course(courses[i]);
    }
}

void print_student(struct student s) {
    printf("Roll no.: %s\n", s.rollno);
    printf("Name: %s\n", s.name);
    printf("Branch(CSE:0,EE:1,ME:2): %d\n", s.branch);
    printf("Semester: %d\n", s.semester);
    printf("List of courses: ");
    for (int i=0; i<s.ncourses; i++) {
        printf("%s    ", s.course_codes[i]);
    }
    printf("\n\n");
}

void print_instructor(struct instructor in) {
	printf("Instructor ID: %s\n", in.id);
	printf("Name: %s\n", in.name);
	printf("List of courses: ");
    for (int i=0; i<in.ncourses; i++) {
        printf("%s    ", in.courses_codes[i]);
    }
    printf("\n\n");
}

void print_course(struct course c) {
    printf("Course code: %s\n", c.code);
    printf("Name: %s\n", c.name);
    printf("Credits: %d\n", c.credits);
    printf("List of Instructors(IDs): ");
    for (int i=0;i<c.ninstructors;i++) {
        printf("%s    ", c.instructor_ids[i]);
    }
    printf("\nList of Students(Roll nos.): ");
    for (int j=0;j<c.nstudents;j++) {
        printf("%s    ", c.student_rollnos[j]);
    }
    printf("\n\n");
}

void modify_student() {
    char mod[MAX];
    int i,n,m;
    printf("Enter rollno of student: ");
    scanf("%s" ,mod);
    for(i=0;i<nstudents;i++) {
        if(strcmp(mod,students[i].rollno) == 0) {
            break;
        }
    }
    if(i == nstudents) {
        printf("Student not found!");
    }
    else{
        printf("Student's Details\n-----------------\n");
        print_student(students[i]);
        printf("\nChoose what do you want to modify: \n\n1.Everything\n2.Roll no\n3.Name\n4.Branch\n5.Semester\n6.Courses\n7.Return to main menu\n\n>>> ");
        int n_c,n_k;
        scanf("%d",&n);
        switch(n) {
            case 1 : printf("Enter new rollno: ");
                     while(1){
                         scanf("%s",mod);
                         int l;
                         for(l=0;l<nstudents;l++) {
                             if(strcmp(mod,students[l].rollno) == 0) {
                                 break;
                                 }
                             }
                         if(strcmp(mod,students[i].rollno) == 0) {
                             break;
                         }
                         if(l == nstudents) {
                             break;
                         }
                         else {
                             printf("Student already exists with the same rollno. Please enter different Roll no. \n\n>>>");
                             continue;
                         }
                         break;
                     }
                     for(n_c=0;n_c<ncourses;n_c++) {
                         for(n_k=0;n_k<courses[n_c].nstudents;n_k++) {
                             if(strcmp(courses[n_c].student_rollnos[n_k],students[i].rollno) == 0) {
                                 strcpy(courses[n_c].student_rollnos[n_k],mod);
                                 break;
                             }
                         }
                     }
                     strcpy(students[i].rollno, mod);
                     printf("Enter new name: ");
                     scanf(" %[^\n]s",students[i].name);
                     printf("Enter new branch(Enter integer 0:CSE,1:EE,2:ME): ");
                     scanf("%u",&students[i].branch);
                     printf("Enter new semester: ");
                     scanf("%d",&students[i].semester);
                     printf("Enter new no. of courses: ");
                     scanf("%d",&students[i].ncourses);
                     printf("Enter course codes(Press Enter after every course code): ");
                     students[i].course_codes = realloc (students[i].course_codes,(students[i].ncourses)*sizeof(char *));
                     for(int j = 0;j<students[i].ncourses;j++) {
                         students[i].course_codes[j] = malloc (MAX*sizeof(char));
                         scanf("%s", students[i].course_codes[j]);
                         int k;
                         for(k=0;k<ncourses;k++){
                             if(strcmp(students[i].course_codes[j],courses[k].code) == 0){
                                 courses[k].nstudents++;
                                 courses[k].student_rollnos = realloc(courses[k].student_rollnos, (courses[k].nstudents) * sizeof(char *));
                                 courses[k].student_rollnos[(courses[k].nstudents)-1] = malloc (MAX * sizeof(char));
                                 strcpy(courses[k].student_rollnos[(courses[k].nstudents)-1], students[i].rollno);
                                 break;
                             }
                         }
                         if(k == ncourses) {
                             default_course_roll(students[i].course_codes[j],students[i].rollno);
                             printf("\n*Default course information has been given to this course. You need to update this course Information afterwards\n");
                             break;
                         }
                     }
                     break;
            case 2 : printf("Enter new rollno: ");
                     while(1){
                         scanf("%s",mod);
                         int l;
                         for(l=0;l<nstudents;l++) {
                             if(strcmp(mod,students[l].rollno) == 0) {
                                 break;
                                 }
                             }
                         if(strcmp(mod,students[i].rollno) == 0) {
                             printf("\nSame Roll no as before. Nothing changed");
                             break;
                         }
                         if(l == nstudents) {
                             break;
                         }
                         else if(l != nstudents) {
                             printf("Student already exists with the same rollno. Please enter different Roll no. \n\n>>>");
                             continue;
                         }
                         break;
                     }
                     for(n_c=0;n_c<ncourses;n_c++) {
                         for(n_k=0;n_k<courses[n_c].nstudents;n_k++) {
                             if(strcmp(courses[n_c].student_rollnos[n_k],students[i].rollno) == 0) {
                                 strcpy(courses[n_c].student_rollnos[n_k],mod);
                                 break;
                             }
                         }
                     }
                     strcpy(students[i].rollno, mod);
                     break;
            case 3 : printf("Enter new name: ");
                     scanf(" %[^\n]s",students[i].name);
                     break;
            case 4 : printf("Enter new branch(Enter integer 0:CSE,1:EE,2:ME): ");
                     scanf("%u",&students[i].branch);
                     break;
            case 5 : printf("Enter new semester: ");
                     scanf("%d",&students[i].semester);
                     break;
            case 6 : printf("Enter new no. of courses: ");
                     scanf("%d",&students[i].ncourses);
                     printf("Enter course codes(Press Enter after every course code): ");
                     students[i].course_codes = realloc (students[i].course_codes,(students[i].ncourses)*sizeof(char *));
                     for(int j = 0;j<students[i].ncourses;j++) {
                         students[i].course_codes[j] = malloc (MAX*sizeof(char));
                         scanf("%s", students[i].course_codes[j]);
                         int k;
                         for(k=0;k<ncourses;k++){
                             if(strcmp(students[i].course_codes[j],courses[k].code) == 0){
                                 courses[k].nstudents++;
                                 courses[k].student_rollnos = realloc(courses[k].student_rollnos, (courses[k].nstudents) * sizeof(char *));
                                 courses[k].student_rollnos[(courses[k].nstudents)-1] = malloc (MAX * sizeof(char));
                                 strcpy(courses[k].student_rollnos[(courses[k].nstudents)-1], students[i].rollno);
                                 break;
                             }
                         }
                         if(k == ncourses) {
                             default_course_roll(students[i].course_codes[j],students[i].rollno);
                             printf("\n*Default course information has been given to this course. You need to update this course Information afterwards\n");
                             break;
                         }
                     }
                     break;
           default : break;
        }
        fprintf_course();
        fprintf_student();
    }
}

void modify_instructor() {
    char mod[MAX];
    int i=0,n;
    printf("Enter the instructor id: ");
    scanf("%s",mod);
     while(i != ninstructors) {
        if(strcmp(mod,instructors[i].id) == 0){
            break;
        }
        i++;
    }
    if(i == nstudents) {
        printf("Instructor not found!");
    }
    else {
        printf("Instructor's Details\n-----------------\n");
        print_instructor(instructors[i]);
        printf("\nChoose what do you want to modify:\n\n1.Everything\n2.Instructor ID\n3.Name\n4.Courses\n5.Main menu\n\n>>> ");
        int n_c,n_k;
        scanf("%d",&n);
        switch(n) {
            case 1 : printf("Enter new instructor id: ");
                     while(1){
                         scanf("%s",mod);
                         int l;
                         for(l=0;l<ninstructors;l++) {
                             if(strcmp(mod,instructors[l].id) == 0) {
                                 break;
                                 }
                             }
                         if(strcmp(mod,instructors[i].id) == 0) {
                             break;
                         }
                         if(l == ninstructors) {
                             break;
                         }
                         else {
                             printf("Instructor already exists with the same id. Please enter different instructor id.\n\n>>>");
                             continue;
                         }
                         break;
                     }
                     for(n_c=0;n_c<ncourses;n_c++) {
                         for(n_k=0;n_k<courses[n_c].ninstructors;n_k++) {
                             if(strcmp(courses[n_c].instructor_ids[n_k],instructors[i].id) == 0) {
                                 strcpy(courses[n_c].instructor_ids[n_k],mod);
                                 break;
                             }
                         }
                     }
                     strcpy(instructors[i].id, mod);
                     printf("Enter new name: ");
                     scanf(" %[^\n]s",instructors[i].name);
                     printf("Enter no. of courses: ");
                     scanf("%d",&instructors[i].ncourses);
                     printf("Enter course codes(Press Enter after every course code): ");
                     instructors[i].courses_codes = realloc (instructors[i].courses_codes, instructors[i].ncourses * sizeof(char *));
                     for(int j = 0;j<instructors[i].ncourses;j++) {
                         instructors[i].courses_codes[j] = malloc (MAX * sizeof(char));
                         scanf("%s", instructors[i].courses_codes[j]);
                         int k;
                         for(k=0;k<ncourses;k++){
                             if(strcmp(instructors[i].courses_codes[j],courses[k].code) == 0){
                                 courses[k].ninstructors++;
                                 courses[k].instructor_ids = realloc(courses[k].instructor_ids, (courses[k].ninstructors) * sizeof(char *));
                                 courses[k].instructor_ids[(courses[k].ninstructors)-1] = malloc (MAX * sizeof(char));
                                 strcpy(courses[k].instructor_ids[(courses[k].ninstructors)-1], instructors[i].id);
                                 break;
                             }
                         }
                         if(k == ncourses) {
                             default_course_id(instructors[i].courses_codes[j],instructors[i].id);
                             printf("\n*Default course information has been given to this course. You need to update this course Information afterwards\n");
                             break;
                         }
                     }
                     break;
            case 2 : printf("Enter new instructor id: ");
                     while(1){
                         scanf("%s",mod);
                         int l;
                         for(l=0;l<ninstructors;l++) {
                             if(strcmp(mod,instructors[l].id) == 0) {
                                 break;
                             }
                         }
                         if(strcmp(mod,instructors[i].id) == 0) {
                             break;
                         }
                         if(l == ninstructors) {
                             break;
                         }
                         else {
                             printf("Instructor already exists with the same id. Please enter different instructor id.\n\n>>>");
                             continue;
                         }
                         break;
                     }
                     for(n_c=0;n_c<ncourses;n_c++) {
                         for(n_k=0;n_k<courses[n_c].ninstructors;n_k++) {
                             if(strcmp(courses[n_c].instructor_ids[n_k],instructors[i].id) == 0) {
                                 strcpy(courses[n_c].instructor_ids[n_k],mod);
                                 break;
                             }
                         }
                     }
                     strcpy(instructors[i].id, mod);
                     break;
            case 3 : printf("Enter new name: ");
                     scanf(" %[^\n]s",instructors[i].name);
                     break;
            case 4 : printf("Enter no. of courses: ");
                     scanf("%d",&instructors[i].ncourses);
                     printf("Enter course codes(Press Enter after every course code): ");
                     instructors[i].courses_codes = realloc (instructors[i].courses_codes, instructors[i].ncourses * sizeof(char *));
                     for(int j = 0;j<instructors[i].ncourses;j++) {
                         instructors[i].courses_codes[j] = malloc (MAX * sizeof(char));
                         scanf("%s", instructors[i].courses_codes[j]);
                         int k;
                         for(k=0;k<ncourses;k++){
                             if(strcmp(instructors[i].courses_codes[j],courses[k].code) == 0){
                                 courses[k].ninstructors++;
                                 courses[k].instructor_ids = realloc(courses[k].instructor_ids, (courses[k].ninstructors) * sizeof(char *));
                                 courses[k].instructor_ids[(courses[k].ninstructors)-1] = malloc (MAX * sizeof(char));
                                 strcpy(courses[k].instructor_ids[(courses[k].ninstructors)-1], instructors[i].id);
                                 break;
                             }
                         }
                         if(k == ncourses) {
                             default_course_id(instructors[i].courses_codes[j],instructors[i].id);
                             printf("\n*Default course information has been given to this course. You need to update this course Information afterwards\n");
                             break;
                         }
                     }
                     break;
           default : break;
        }
        fprintf_course();
        fprintf_instructor();
    }
}

void modify_course() {
    char mod[MAX];
    int i=0,n;
    printf("Enter course code: ");
    scanf("%s", mod);
    while(i != ncourses) {
        if(strcmp(mod, courses[i].code) == 0){
            break;
        }
        i++;
    }
    if(i == ncourses) {
        printf("Course not found!");
    }
    else {
        printf("Course's Details\n-----------------\n");
        print_course(courses[i]);
        printf("\nChoose what you want to modify:\n\n1.Everything\n2.Course code\n3.Course name\n4.No. of credits\n5.Instructors associated\n6.Students enrolled\n7.Main menu\n\n>>> ");
        int n_c,n_k,n_s,n_i;
        scanf("%d",&n);
        switch(n) {
            case 1 : printf("Enter new course code: ");
                     while(1){
                         scanf("%s",mod);
                         int l;
                         for(l=0;l<ncourses;l++) {
                             if(strcmp(mod,courses[l].code) == 0) {
                                 break;
                                 }
                             }
                         if(strcmp(mod,courses[i].code) == 0) {
                             break;
                         }
                         if(l == ncourses) {
                             break;
                         }
                         else {
                             printf("Course already exists with the same course code. Please enter different course code \n\n>>>");
                             continue;
                         }
                         break;
                     }
                     for(n_c=0;n_c<nstudents;n_c++) {
                         for(n_k=0;n_k<students[n_c].ncourses;n_k++) {
                             if(strcmp(students[n_c].course_codes[n_k],courses[i].code) == 0) {
                                 strcpy(students[n_c].course_codes[n_k],mod);
                                 break;
                             }
                         }
                     }
                     for(n_s=0;n_s<ninstructors;n_s++) {
                         for(n_i=0;n_i<instructors[n_s].ncourses;n_i++) {
                             if(strcmp(instructors[n_s].courses_codes[n_i],courses[i].code) == 0) {
                                 strcpy(instructors[n_s].courses_codes[n_i],mod);
                                 break;
                             }
                         }
                     }
                     strcpy(courses[i].code, mod);
                     printf("Enter new course name: ");
                     scanf(" %[^\n]s", courses[i].name);
                     printf("Enter new no. of credits: ");
                     scanf("%d",&courses[i].credits);
                     printf("Enter new no. of instructors: ");
                     scanf("%d",&courses[i].ninstructors);
                     printf("Enter ids of these instructors(Press Enter after every instructor's id): ");
                     courses[i].instructor_ids = realloc (courses[i].instructor_ids, (courses[i].ninstructors) * sizeof(char *));
                     for(int j=0;j<courses[i].ninstructors;j++) {
                         courses[i].instructor_ids[j] = malloc (MAX * sizeof(char));
                         scanf("%s",courses[i].instructor_ids[j]);
                         int k;
                         for(k=0;k<ninstructors;k++) {
                             if(strcmp(courses[i].instructor_ids[j],instructors[k].id) == 0) {
                                 instructors[k].ncourses++;
                                 instructors[k].courses_codes = realloc (instructors[k].courses_codes, instructors[k].ncourses * sizeof(char *));
                                 instructors[k].courses_codes[instructors[k].ncourses-1] = malloc (MAX * sizeof(char));
                                 strcpy(instructors[k].courses_codes[instructors[k].ncourses-1],courses[i].code);
                                 break;
                             }
                         }
                         if(k == ninstructors) {
                             default_instructor(courses[i].instructor_ids[j],courses[i].code);
                             printf("\n*Default instructor information has been given to this new instructor.You need to update this information afterwards.\n");
                         }
                     }
                     printf("Enter new no. of students: ");
                     scanf("%d",&courses[i].nstudents);
                     printf("Enter rollnos of these students(Press Enter after every student's rollno): ");
                     courses[i].student_rollnos = realloc (courses[i].student_rollnos, (courses[i].nstudents) * sizeof(char *));
                     for(int j=0;j<courses[i].nstudents;j++) {
                         courses[i].student_rollnos[j] = malloc (MAX * sizeof(char));
                         scanf("%s",courses[i].student_rollnos[j]);
                         int k;
                         for(k=0;k<nstudents;k++) {
                             if(strcmp(courses[i].student_rollnos[j],students[k].rollno) == 0) {
                                 students[k].ncourses++;
                                 students[k].course_codes = realloc (students[k].course_codes, students[k].ncourses * sizeof(char *));
                                 students[k].course_codes[students[k].ncourses-1] = malloc (MAX * sizeof(char));
                                 strcpy(students[k].course_codes[students[k].ncourses-1],courses[i].code);
                                 break;
                             }
                         }
                         if(k == nstudents) {
                             default_student(courses[i].student_rollnos[j],courses[i].code);
                             printf("\n*Default student information has been given to this new student.You need to update this information afterwards.\n");
                         }
                     }
                     break;
            case 2 : printf("Enter new course code: ");
                     while(1){
                         scanf("%s",mod);
                         int l;
                         for(l=0;l<ncourses;l++) {
                             if(strcmp(mod,courses[l].code) == 0) {
                                 break;
                                 }
                             }
                         if(strcmp(mod,courses[i].code) == 0) {
                             break;
                         }
                         if(l == ncourses) {
                             break;
                         }
                         else {
                             printf("Course already exists with the same course code. Please enter different course code \n\n>>>");
                             continue;
                         }
                         break;
                     }
                     for(n_c=0;n_c<nstudents;n_c++) {
                         for(n_k=0;n_k<students[n_c].ncourses;n_k++) {
                             if(strcmp(students[n_c].course_codes[n_k],courses[i].code) == 0) {
                                 strcpy(students[n_c].course_codes[n_k],mod);
                                 break;
                             }
                         }
                     }
                     for(n_s=0;n_s<ninstructors;n_s++) {
                         for(n_i=0;n_i<instructors[n_s].ncourses;n_i++) {
                             if(strcmp(instructors[n_s].courses_codes[n_i],courses[i].code) == 0) {
                                 strcpy(instructors[n_s].courses_codes[n_i],mod);
                                 break;
                             }
                         }
                     }
                     strcpy(courses[i].code, mod);
                     break;
            case 3 : printf("Enter new course name: ");
                     scanf(" %[^\n]s", courses[i].name);
                     break;
            case 4 : printf("Enter new no. of credits: ");
                     scanf("%d",&courses[i].credits);
                     break;
            case 5 : printf("Enter new no. of instructors: ");
                     scanf("%d",&courses[i].ninstructors);
                     printf("Enter ids of these instructors(Press Enter after every instructor's id): ");
                     courses[i].instructor_ids = realloc (courses[i].instructor_ids, (courses[i].ninstructors) * sizeof(char *));
                     for(int j=0;j<courses[i].ninstructors;j++) {
                         courses[i].instructor_ids[j] = malloc (MAX * sizeof(char));
                         scanf("%s",courses[i].instructor_ids[j]);
                         int k;
                         for(k=0;k<ninstructors;k++) {
                             if(strcmp(courses[i].instructor_ids[j],instructors[k].id) == 0) {
                                 instructors[k].ncourses++;
                                 instructors[k].courses_codes = realloc (instructors[k].courses_codes, instructors[k].ncourses * sizeof(char *));
                                 instructors[k].courses_codes[instructors[k].ncourses-1] = malloc (MAX * sizeof(char));
                                 strcpy(instructors[k].courses_codes[instructors[k].ncourses-1],courses[i].code);
                                 break;
                             }
                         }
                         if(k == ninstructors) {
                             default_instructor(courses[i].instructor_ids[j],courses[i].code);
                             printf("\n*Default instructor information has been given to this new instructor.You need to update this information afterwards.\n");
                         }
                     }
                     break;
            case 6 : printf("Enter new no. of students: ");
                     scanf("%d",&courses[i].nstudents);
                     printf("Enter rollnos of these students(Press Enter after every student's rollno): ");
                     courses[i].student_rollnos = realloc (courses[i].student_rollnos, (courses[i].nstudents) * sizeof(char *));
                     for(int j=0;j<courses[i].nstudents;j++) {
                         courses[i].student_rollnos[j] = malloc (MAX * sizeof(char));
                         scanf("%s",courses[i].student_rollnos[j]);
                         int k;
                         for(k=0;k<nstudents;k++) {
                             if(strcmp(courses[i].student_rollnos[j],students[k].rollno) == 0) {
                                 students[k].ncourses++;
                                 students[k].course_codes = realloc (students[k].course_codes, students[k].ncourses * sizeof(char *));
                                 students[k].course_codes[students[k].ncourses-1] = malloc (MAX * sizeof(char));
                                 strcpy(students[k].course_codes[students[k].ncourses-1],courses[i].code);
                                 break;
                             }
                         }
                         if(k == nstudents) {
                             default_student(courses[i].student_rollnos[j],courses[i].code);
                             printf("\n*Default student information has been given to this new student.You need to update this information afterwards.\n");
                         }
                     }
                     break;
           default : break;
        }
        fprintf_student();
        fprintf_instructor();
        fprintf_course();
    }
}

void load_records() {
    load_students();
    load_instructors();
    load_courses();
}

void load_students() {
    fps = fopen(students_file, "r");
    int nstudents;
    char buf[MAX];
    struct student s;
    fscanf(fps, "%d", &nstudents);
    for (int i=0; i<nstudents; i++) {
        fgets(buf, MAX, fps);
        fscanf(fps, "%s", s.rollno);
        fscanf(fps, " %[^\n]s", s.name);
        fscanf(fps, "%u", &s.branch);
        fscanf(fps, "%d", &s.semester);
        fscanf(fps, "%d", &s.ncourses);
        s.course_codes = malloc (s.ncourses * sizeof(char *));
        for (int j=0; j<s.ncourses; j++) {
            s.course_codes[j] = malloc (MAX * sizeof (char));
            fscanf(fps, "%s", s.course_codes[j]);
        }
        add_student(s);
    }
    fclose(fps);
}

void load_instructors() {
	fpi = fopen(instructors_file,"r");
	int ninstructors;
	char buf[MAX];
	struct instructor in;
	fscanf(fpi,"%d",&ninstructors);
	for (int i=0;i<ninstructors;i++) {
		fgets(buf,MAX,fpi);
		fscanf(fpi, "%s", in.id);
		fscanf(fpi, " %[^\n]s", in.name);
		fscanf(fpi, "%d", &in.ncourses);
		in.courses_codes = malloc (in.ncourses * sizeof(char *));
        for (int j=0; j<in.ncourses; j++) {
            in.courses_codes[j] = malloc (MAX * sizeof (char));
            fscanf(fpi, "%s", in.courses_codes[j]);
        }
        add_instructor(in);
	}
	fclose(fpi);
}

void load_courses() {
    fpc = fopen(courses_file,"r");
    int ncourses;
    char buf[MAX];
    struct course c;
    fscanf(fpc,"%d",&ncourses);
    for(int i=0;i<ncourses;i++) {
        fgets(buf,MAX,fpc);
        fscanf(fpc,"%s",c.code);
        fscanf(fpc," %[^\n]s",c.name);
        fscanf(fpc,"%d",&c.credits);
        fscanf(fpc,"%d",&c.ninstructors);
        c.instructor_ids = malloc (c.ninstructors * sizeof(char *));
        for(int j=0;j<c.ninstructors;j++){
            c.instructor_ids[j] = malloc (MAX * sizeof(char));
            fscanf(fpc, "%s", c.instructor_ids[j]);
        }
        fscanf(fpc,"%d",&c.nstudents);
        c.student_rollnos = malloc (c.nstudents * sizeof(char *));
        for(int j=0;j<c.nstudents;j++){
            c.student_rollnos[j] = malloc (MAX * sizeof(char));
            fscanf(fpc, "%s", c.student_rollnos[j]);
        }
        add_course(c);
    }
    fclose(fpc);
}
