import QtQuick 2.0
import QtLocation 5.9
import QtPositioning 5.8

Rectangle {
    id: window
    width: 800 // Définir la largeur souhaitée
    height: 600 // Définir la hauteur souhaitée

    property double latitude: 36.8984 // Latitude approximative du centre d'Ariana
    property double longitude: 10.1897 // Longitude approximative du centre d'Ariana

    Plugin {
        id: googlemapview
        name: "osm"
    }

    Map {
        id: mapview
        anchors.fill: parent
        plugin: googlemapview
        center: QtPositioning.coordinate(latitude, longitude)
        zoomLevel: 10 // Niveau de zoom pour voir la zone d'Ariana en détail

        MapPolygon {
            path: [
                QtPositioning.coordinate(36.8921, 10.1624), // Coin nord-ouest d'Ariana
                QtPositioning.coordinate(36.9160, 10.1624), // Coin nord-est d'Ariana
                QtPositioning.coordinate(36.9160, 10.2164), // Coin sud-est d'Ariana
                QtPositioning.coordinate(36.8921, 10.2164), // Coin sud-ouest d'Ariana
            ]
            color: "blue" // Couleur de remplissage du polygone
        }
    }

    function setCenterPosition(lati, longi) {
        mapview.pan(latitude - lati, longitude - longi)
        latitude = lati
        longitude = longi
    }

    function setLocationMarking(lati, longi) {
        var item = maplocationmarker.createObject(mapview, {
            coordinate: QtPositioning.coordinate(lati, longi)
        })
        mapview.addMapItem(item)
    }

    Component {
        id: maplocationmarker
        MapQuickItem {
            anchorPoint.x: image.width / 2
            anchorPoint.y: image.height
            coordinate: QtPositioning.coordinate(0, 0)
            sourceItem: Image {
                id: image
                width: 40
                height: 40
                source: "https://cdn.iconscout.com/icon/free/png-256/map-marker-1769323-1506940.png"
            }
        }
    }
}
