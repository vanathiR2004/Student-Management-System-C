#include <stdio.h>
#include <string.h>
#include <math.h>

struct Student
{
    int Rollno;
    char Name[50];
    int Age;
    char Gender;
    char Department[50];
    float Marks;
};

void addStudent();
void DisplayStudent();
void SearchStudent();
void UpdateStudent();
void DeleteStudent();
void ClassAverage();
void DisplayStudentAll();

int main()
{
    int choice;
    do
    {
        printf("****************************\n");
        printf(" STUDENT MANAGEMENT SYSTEM\n");
        printf("****************************\n");
        printf("1.Add Student\n2.Display Student\n3.Display Students(All)\n4.Search Student\n5.Update Student\n6.Delete Student\n7.Class Average\n8.Exit\n");
        printf("Enter Your Choice:");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addStudent();
            break;
        case 2:
            DisplayStudent();
            break;
        case 3:
            DisplayStudentAll();
            break;
        case 4:
            SearchStudent();
            break;
        case 5:
            UpdateStudent();
            break;
        case 6:
            DeleteStudent();
            break;
        case 7:
            ClassAverage();
            break;
        case 8:
            printf("Thank You!\n");
            break;
        default:
            printf("Invalid Choice\n");
        }
    } while (choice != 8);

    return 0;
}

void addStudent()
{
    int found = 0;
    struct Student s;
    struct Student temp;
    FILE *fp;
    do
    {
        found = 0;

        printf("Enter Roll No: ");
        scanf("%d", &s.Rollno);

        fp = fopen("students.dat", "rb");

        if (fp != NULL)
        {
            while (fread(&temp, sizeof(struct Student), 1, fp))
            {
                if (temp.Rollno == s.Rollno)
                {
                    found = 1;
                    printf("This Roll Number already exists!\n");
                    break;
                }
            }

            fclose(fp);
        }

    } while (found == 1);

    printf("Enter Name:");
    scanf("%s", s.Name);
    printf("Enter Age:");
    scanf("%d", &s.Age);
    printf("Enter Gender:");
    scanf(" %c", &s.Gender);
    printf("Enter Department:");
    scanf("%s", s.Department);
    printf("Enter Marks:");
    scanf("%f", &s.Marks);
    fp = fopen("students.dat", "ab");
    if (fp == NULL)
    {
        printf("Unable to open file!");
        return;
    }
    fwrite(&s, sizeof(struct Student), 1, fp);
    fclose(fp);
    printf("\n Student Added Successfully!!!\n");
}

void DisplayStudent()
{
    struct Student s;
    FILE *fp;
    char dept[50];
    int found = 0;

    printf("Enter Department to display:");
    scanf("%s", dept);

    fp = fopen("students.dat", "rb");
    if (fp == NULL)
    {
        printf("No recodrs found!!!!\n");
        return;
    }
    printf("\n*************************\n");
    printf("\n   STUDENT DETAILS\n");
    printf("\n*************************\n");
    while (fread(&s, sizeof(struct Student), 1, fp))
    {
        if (strcmp(s.Department, dept) == 0)
        {
            found == 1;
            printf("RollNo    : %d\n", s.Rollno);
            printf("Name      : %s\n", s.Name);
            printf("Age       : %d\n", s.Age);
            printf("Gender    : %c\n", s.Gender);
            printf("Department: %s\n", s.Department);
            printf("Marks     : %.2f\n", s.Marks);
            printf("\n*************************\n");
        }
    }

    fclose(fp);
}

void SearchStudent()
{
    int roll;
    int found = 0;
    struct Student s;
    FILE *fp;
    fp = fopen("students.dat", "rb");
    if (fp == NULL)
    {
        printf("No recodrs found!!!!\n");
        return;
    }
    printf("Enter RollNo to be searched:");
    scanf("%d", &roll);
    while (fread(&s, sizeof(struct Student), 1, fp))
    {
        if (s.Rollno == roll)
        {
            printf("\n*************************\n");
            printf("\n   STUDENT DETAILS\n");
            printf("\n*************************\n");
            printf("RollNo    : %d\n", s.Rollno);
            printf("Name      : %s\n", s.Name);
            printf("Age       : %d\n", s.Age);
            printf("Gender    : %d\n", s.Gender);
            printf("Department: %s\n", s.Department);
            printf("Marks     : %f\n", s.Marks);
            printf("\n*************************\n");
            found = 1;
            break;
        }
    }
    if (found == 0)
    {
        printf("No Such Student Found!\n");
    }
    fclose(fp);
}

void DeleteStudent()
{
    int roll;
    int found = 0;
    struct Student s;
    FILE *fp;
    FILE *temp;
    fp = fopen("students.dat", "rb");
    if (fp == NULL)
    {
        printf("No recodrs found!!!!\n");
        return;
    }
    temp = fopen("temporary.dat", "wb");
    printf("Enter Roll no to be deleted:");
    scanf("%d", &roll);

    while (fread(&s, sizeof(struct Student), 1, fp))
    {
        if (s.Rollno == roll)
        {
            found = 1;
        }
        else
        {
            fwrite(&s, sizeof(struct Student), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);
    remove("students.dat");
    rename("temporary.dat", "students.dat");
    if (found == 1)
    {
        printf("Student Deleted Successfully!\n");
    }
    else
    {
        printf("Student Not Found!\n");
    }
    if (found == 1)
    {
        printf("Deleted the data successfully!!\n");
    }
}

void UpdateStudent()
{
    int roll;
    int found = 0;
    struct Student s;
    FILE *fp;
    FILE *temp;
    fp = fopen("students.dat", "rb");
    temp = fopen("temporary.dat", "wb");
    if (fp == NULL)
    {
        printf("No recodrs found!!!!\n");
        return;
    }
    if (temp == NULL)
    {
        printf("Unable to create temporary file!\n");
        fclose(fp);
        return;
    }
    printf("Enter RollNo to update:");
    scanf("%d", &roll);
    while (fread(&s, sizeof(struct Student), 1, fp))
    {
        if (s.Rollno == roll)
        {
            printf("Enter new Name:");
            scanf("%s", s.Name);
            printf("Enter new Age:");
            scanf("%d", &s.Age);
            printf("Enter Gender:");
            scanf(" %c", &s.Gender);
            printf("Enter new Department:");
            scanf("%s", s.Department);
            printf("Enter new marks:");
            scanf("%f", &s.Marks);
            fwrite(&s, sizeof(struct Student), 1, temp);
            found = 1;
        }
        else
        {
            fwrite(&s, sizeof(struct Student), 1, temp);
        }
    }
    if (found == 1)
    {
        printf("student updated Successfully!\n");
    }
    else
    {
        printf("Student not Found!\n");
    }
    fclose(fp);
    fclose(temp);

    remove("students.dat");
    rename("temporary.dat", "students.dat");
}

void ClassAverage()
{
    int n = 0;
    float avg, sum = 0.0;
    struct Student s;
    char dept[50];
    printf("Enter Department:");
    scanf("%s", dept);
    FILE *fp;
    fp = fopen("students.dat", "rb");
    if (fp == NULL)
    {
        printf("No recodrs found!!!!\n");
        return;
    }
    while (fread(&s, sizeof(struct Student), 1, fp))
    {
        if (strcmp(s.Department, dept) == 0)
        {
            sum = sum + s.Marks;
            n++;
        }
    }
    if (n == 0)
    {
        printf("No student records found.\n");
        fclose(fp);
        return;
    }
    fclose(fp);
    avg = sum / n;
    printf("Average of the class: %.2f\n", avg);
}

void DisplayStudentAll()
{
    struct Student s;
    FILE *fp;

    fp = fopen("students.dat", "rb");
    if (fp == NULL)
    {
        printf("No recodrs found!!!!\n");
        return;
    }
    printf("\n*************************\n");
    printf("\n   STUDENT DETAILS\n");
    printf("\n*************************\n");
    while (fread(&s, sizeof(struct Student), 1, fp))
    {

        printf("RollNo    : %d\n", s.Rollno);
        printf("Name      : %s\n", s.Name);
        printf("Age       : %d\n", s.Age);
        printf("Gender    : %c\n", s.Gender);
        printf("Department: %s\n", s.Department);
        printf("Marks     : %.2f\n", s.Marks);
        printf("\n*************************\n");
    }

    fclose(fp);
}
