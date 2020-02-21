from rest_framework.response import Response
from rest_framework import viewsets
from rest_framework.views import APIView

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
        dir_x, dir_y = posted.get("x", 0), posted.get("y", 0)
        print(dir_x, dir_y)

        # TODO: dustcartにコマンドを送信
        # TODO: 非同期で早期リターン Celery+redis ?
        #   OR ここでdustcartからの動画(UDP) Listenする？

        # TODO: log/actions,log/imagesに保存

        return Response({'succeeded': True})
