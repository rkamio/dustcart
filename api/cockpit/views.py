from rest_framework.response import Response
from rest_framework import viewsets
from rest_framework.views import APIView

from socket import socket, AF_INET, SOCK_DGRAM

from .models import Dustcart
from .serializer import DustcartSerializer


class DustcartViewSet(viewsets.ModelViewSet):
    queryset = Dustcart.objects.all()
    serializer_class = DustcartSerializer


class CockpitAPI(APIView):

    def get(self, request, format=None):
        # dustcartのダッシュボード(センサー値とか)返す？
        return Response({"succeeded": True})

    # TODO: 速度出なかったらWebSocket or UDP
    def post(self, request):
        posted = request.data
        print("posted data: ", posted)

        self.command = posted.get("command")
        self.port = posted.get("port")
        self.address = posted.get("address")

        self.send_command()

        # TODO: 非同期で早期リターン Celery+redis ?
        #   OR ここでdustcartからの動画(UDP) Listenする？

        # TODO: log/actions,log/imagesに保存

        return Response({'succeeded': True})

    def send_command(self):
        dustcart_socket = socket(AF_INET, SOCK_DGRAM)
        dustcart_socket.sendto(
            self.command.encode(),
            (self.address, self.port)
            )
        dustcart_socket.close()
        print("send_command done.")
