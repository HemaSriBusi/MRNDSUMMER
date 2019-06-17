from django.views import View
from onlineapp.models import *
from django.shortcuts import render,redirect
from onlineapp.form.colleges import *
from onlineapp.form.students import *
from django.urls import resolve
from django.shortcuts import get_object_or_404
from django.contrib.auth.mixins import LoginRequiredMixin

class StudentView(View):
    def get(self,request,*args,**kwargs):
        students = Student.objects.filter(**kwargs)
        return render(
            request,
            template_name="onlineapp/students.html",
            context={
                'students':students,
                'id':kwargs['id'],
                'user_permissions': request.user.get_all_permissions(),
            }
        )

class AddStudentView(View):

    def get(self,request,*args,**kwargs):
        StuForm = Student_Form()
        MockForm = Mock_Form()


        if resolve(request.path_info).url_name == "deleteStudent":
            Student.objects.get(pk=kwargs.get('id')).delete()
            return redirect('/colleges')

        if resolve(request.path_info).url_name == 'editStudent':
            print(kwargs)
            student = get_object_or_404(Student, **kwargs)
            mocktest1 = MockTest1.objects.get(student=student)
            StuForm = Student_Form(instance=student)
            MockForm = Mock_Form(instance=mocktest1)

        return render(
            request,
            template_name="onlineapp/addStudent.html",
            context={
                'form1': StuForm,
                'form2' :MockForm,
                'user_permissions': request.user.get_all_permissions(),
            }
        )

    def post(self,request,*args,**kwargs):


        if resolve(request.path_info).url_name == 'editStudent':
            student = get_object_or_404(Student, **kwargs)
            s_form = Student_Form(request.POST, instance=student)
            total_marks = 0
            for i in range(1, 5):
                total_marks += int(request.POST['problem' + str(i)])
            mock = MockTest1.objects.get(student=student)
            mock.total = total_marks
            m_form = Mock_Form(request.POST, instance=mock)
            if m_form.is_valid():
                m_form.save()
                return redirect('/colleges')
            else:
                return render(
                    request,
                    template_name="onlineapp/add_student.html",
                    context={
                        'form1': s_form,
                        'form2': m_form,
                        'user_permissions': request.user.get_all_permissions(),
                    }
                )

        else:
            college = College.objects.get(**kwargs)
            student_form = Student_Form(request.POST)
            mocktest_form = Mock_Form(request.POST)

            if student_form.is_valid():
                student = student_form.save(commit=False)
                student.college = college
                student.save()
                if mocktest_form.is_valid():
                    mocktest = mocktest_form.save(commit=False)
                    mocktest.student = student
                    total_marks = 0
                    for i in range(1, 5):
                        total_marks += int(request.POST['problem' + str(i)])
                    mocktest.total = total_marks
                    mocktest.save()
                    print(mocktest)
                    return redirect('/colleges')

