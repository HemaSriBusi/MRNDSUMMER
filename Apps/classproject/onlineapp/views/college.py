from django.views import View
from onlineapp.models import *
from django.shortcuts import render,redirect
from onlineapp.form.colleges import *
from onlineapp.form.students import *
from django.urls import resolve
from django.shortcuts import get_object_or_404
from django.contrib.auth.mixins import LoginRequiredMixin


class CollegeView(LoginRequiredMixin,View):
    login_url = '/login/'
    def get(self,request,*args,**kwargs):
        if kwargs:
            college = College.objects.get(**kwargs)
            students = list(college.student_set.order_by("-mocktest1__total"))
            #student = Student.objects.filter(**kwargs)
            #colleges = College.objects.all()
            return render(
                request,
                #template_name="onlineapp/colleges.html",
                template_name="onlineapp/college_details.html",
                context= {
                    'colleges':college,
                    'students':students,
                    'user_permissions': request.user.get_all_permissions(),
                    'title' : 'Student from {} | Mentor App'.format(college.name)
                }
            )
        else:
            colleges = College.objects.all()
            return render(
                request,
                template_name="onlineapp/colleges.html",
                context= {
                    'colleges': colleges,
                    'user_permissions': request.user.get_all_permissions(),
                }
            )

class AddCollegeView(View):

    def get(self,request,**kwargs):
        form = AddCollege()

        if kwargs:
            college = College.objects.get(**kwargs)
            form = AddCollege(instance=college)

        return render(
            request,
            template_name="onlineapp/addCollege.html",
            context={
                'form': form,
                'user_permissions': request.user.get_all_permissions(),
            }
        )
    def post(self,request,**kwargs):

        if resolve(request.path_info).url_name == "deleteCollege":
            College.objects.get(pk=kwargs.get('pk')).delete()
            return redirect('/colleges')

        if resolve(request.path_info).url_name == "editCollege":
            college = College.objects.get(pk=kwargs.get('pk'))
            form = AddCollege(request.POST,instance=college)

            if form.is_valid():
                form.save()
                return redirect('/colleges')
        else:

            form = AddCollege(request.POST)
            if form.is_valid():
                form.save()
                return redirect('/colleges')
            return render(
                request,
                template_name="onlineapp/addCollege.html",
                context={
                    'form': form,
                    'user_permissions': request.user.get_all_permissions(),
                }
            )


