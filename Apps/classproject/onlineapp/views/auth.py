from django.views import View
from django.shortcuts import render,redirect
from onlineapp.form.auth import *
from django.contrib.auth import authenticate,login,logout
from django.contrib.auth.models import User
from django.db.utils import *
from django.contrib import messages


class LoginView(View):
    def get(self,request,*args,**kwargs):
        if request.user.is_authenticated:
            return redirect('/colleges')
        form = LoginForm()
        return render(
            request,
            template_name='onlineapp/login.html',
            context={
                'form': form,
            }
        )

    def post(self,request,*args,**kwargs):
        form = LoginForm(request.POST)
        if form.is_valid():
            username=form.cleaned_data['username']
            password=form.cleaned_data['password']
            user = authenticate(
                request,
                username=username,
                password=password
            )
            if user is not None:
                login(request,user)
                return redirect('/colleges')
            else:
                messages.error(request,'Invalid user credentials')
        return render(
            request,
            template_name="onlineapp/login.html",
            context={
                'form':form,
            }
        )

class SignupView(View):
    def get(self,request):
        form = SignUpForm()
        return render(
            request,
            template_name='onlineapp/signup.html',
            context={
                'form': form,
            }
        )

    def post(self,request,*args,**kwargs):
        form = SignUpForm(request.POST)

        if form.is_valid():
            user = User.objects.create_user(**form.cleaned_data)
            user.save()
            print("post")
            if user is not None:
                #login(request,user)
                return redirect('/login')
            else:
                messages.error(request,'Invalid user credentials')

        else:
            return render(
                request,
                template_name='onlineapp/signup.html',
                context={
                    'form': form,
                }
            )
def logout_user(request):
    logout(request)
    return redirect('/login')
