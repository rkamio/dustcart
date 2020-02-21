from rest_framework import routers
from .views import DustcartViewSet, CockpitAPI
from django.urls import re_path
from rest_framework.urlpatterns import format_suffix_patterns

router = routers.SimpleRouter()
router.register(r'dustcarts', DustcartViewSet)

urlpatterns = [
    re_path(r'cockpit', CockpitAPI.as_view())
]

urlpatterns += router.urls
urlpatterns = format_suffix_patterns(urlpatterns)
