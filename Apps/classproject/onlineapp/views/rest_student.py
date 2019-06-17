from rest_framework import status
from rest_framework.views import APIView
from onlineapp.Serializer import *
from onlineapp.models import *
from rest_framework.response import Response
from rest_framework.authentication import *
from rest_framework.permissions import *


class StudentAPIView(APIView):
    authentication_classes = (BasicAuthentication, TokenAuthentication,SessionAuthentication)
    permission_classes = (IsAuthenticated,)

    def get(self,request,*args,**kwargs):
        if 'cpk' in kwargs.keys() and 'spk' in kwargs.keys():
            college = College.objects.get(id=self.kwargs['cpk'])
            serializer = StudentDetailsSerializer(Student.objects.filter(college=college).get(id=kwargs['spk']))
            return Response(serializer.data,status=status.HTTP_201_CREATED)

        elif 'cpk' in kwargs.keys():
            print(kwargs['cpk'])
            college = College.objects.get(id=self.kwargs['cpk'])
            serializer = StudentDetailsSerializer(Student.objects.filter(college=college),many=True)
            return Response(serializer.data,status=status.HTTP_201_CREATED)

        else:
            student = Student.objects.all()
            serializer = StudentDetailsSerializer(student,many=True)
            return Response(serializer.data, status=status.HTTP_201_CREATED)

        return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)

    def post(self,request,*args,**kwargs):
        if 'cpk' in kwargs.keys():
            college = College.objects.get(id=kwargs['cpk'])
            serializer = StudentDetailsSerializer(data=request.data)
            if serializer.is_valid():
                student = serializer.save(college=college)
                student.save()
                return Response(serializer.data, status=status.HTTP_201_CREATED)
            return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)

    def put(self,request,*args,**kwargs):
        if 'spk' in kwargs.keys():
            student = Student.objects.get(id=kwargs['spk'])
            serializer = StudentDetailsSerializer(data=request.data)
            if serializer.is_valid():
                serializer.save()
                return Response(serializer.data, status=status.HTTP_201_CREATED)
            return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)


    def delete(self,request,*args,**kwargs):
        if 'cpk' in kwargs.keys() and 'spk' in kwargs.keys():
            student = Student.objects.get(id=kwargs['spk'])
            student.delete()
            return Response(status=status.HTTP_204_NO_CONTENT)
