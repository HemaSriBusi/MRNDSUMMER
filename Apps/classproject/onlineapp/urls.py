from django.contrib import admin
from django.urls import path
from django.conf import settings
from django.conf.urls import include, url  # For django versions before 2.0
from django.urls import include # For django versions from 2.0 and up
from onlineapp import views
from onlineapp import urls
from .views import *
from onlineapp import funcviews

urlpatterns = [
    path('testpath/',funcviews.my_first_view ),
    path('api/v1/colleges/',CollegeListView.as_view(),name="CollegeAPI"),
    path('api/v1/colleges/<int:id>',college_details_idView.as_view(),name="CollegeDetailsAPI"),
    path('api/v1/colleges/<int:cpk>/students',StudentAPIView.as_view(),name="ClgStudentsDetailsAPI"),
    path('api/v1/colleges/<int:cpk>/students/<int:spk>',StudentAPIView.as_view(),name="ClgStudentDetailsAPI"),
    path('api/v1/students/<int:spk>',StudentAPIView.as_view(),name="StuDetails"),
    path('api/v1/students/',StudentAPIView.as_view(),name="AllStudentsDetailsAPI"),
    path('colleges/',CollegeView.as_view(),name="colleges.html"),
    path('students/<int:pk>/',StudentView.as_view(),name="students.html"),
    path('colleges/<int:pk>/',CollegeView.as_view(),name="college_details"),
    path('colleges/<str:acronym>/',CollegeView.as_view(),name="college_details"),
    path('addCollege/',AddCollegeView.as_view(),name = "addCollege"),
    path('colleges/<int:pk>/edit',AddCollegeView.as_view(),name = "editCollege"),
    path('colleges/<int:pk>/delete',AddCollegeView.as_view(),name = "deleteCollege"),
    path('colleges/<int:pk>/addStudent/',AddStudentView.as_view(),name="addStudent"),
    path('colleges/<int:id>/student/edit', AddStudentView.as_view(), name="editStudent"),
    path('colleges/<int:id>/student/delete', AddStudentView.as_view(), name="deleteStudent"),
    path('login/',LoginView.as_view(),name='login'),
    path('signup/',SignupView.as_view(),name='signup'),
    path('logout/',views.logout_user,name='logout'),
]

