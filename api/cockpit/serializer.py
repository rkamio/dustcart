from rest_framework import serializers

from .models import Dustcart


class DustcartSerializer(serializers.ModelSerializer):
    class Meta:
        model = Dustcart
        fields = (
            "id",
            "name",
            "ip_address"
        )
