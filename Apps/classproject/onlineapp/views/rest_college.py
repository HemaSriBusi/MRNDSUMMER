from rest_framework.decorators import api_view
from rest_framework import status
from rest_framework.views import APIView
from onlineapp.Serializer import *
from onlineapp.models import *
from rest_framework.response import Response
from rest_framework.authentication import *
from rest_framework.permissions import *

class CollegeListView(APIView):
    authentication_classes = (BasicAuthentication,TokenAuthentication,SessionAuthentication)
    permission_classes = (IsAuthenticated,)
    def get(self,request,*args,**kwargs):
        college = College.objects.all()
        serialize = CollegeSerializer(college,many=True)
        return Response(serialize.data)

    def post(self,request,*args,**kwargs):
        serializer = CollegeSerializer(data=request.data)
        if serializer.is_valid():
            serializer.save()
            return Response(serializer.data, status=200)
        return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)



class college_details_idView(APIView):
    authentication_classes = (BasicAuthentication, TokenAuthentication,SessionAuthentication)
    permission_classes = (IsAuthenticated,)
    def get(self, request, *args, **kwargs):
        college = College.objects.filter(id=kwargs['id'])
        serializer = CollegeSerializer(college,many=True)
        return Response(serializer.data)

    def put(self, request, *args, **kwargs):
        college = College.objects.get(id=kwargs['id'])
        serializer = CollegeSerializer(instance=college,data=request.data)
        if serializer.is_valid():
            serializer.save()
            return Response(serializer.data)
        return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)

    def delete(self, request, *args, **kwargs):
        college = College.objects.filter(id=kwargs['id'])
        college.delete()
        return Response(status=status.HTTP_204_NO_CONTENT)
