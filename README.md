# Bus Simulator 3D - Unreal Engine 5

Un simulateur de conduite de bus 3D réaliste créé avec **Unreal Engine 5** (version 5.4).

## 🎮 Fonctionnalités

### ✅ Implémenté
- **Système de physique réaliste**
  - Modèle de traction réaliste
  - Résistance aérodynamique dynamique
  - Résistance de roulement
  - Suspension avec 4 roues indépendantes
  - Modèle d'adhérence des pneus (Pacejka simplifiée)

- **Système de transmission**
  - Moteur à combustion interne simulé
  - 6 vitesses + marche arrière
  - Transmission automatique intelligente
  - Gestion RPM et couple moteur
  - Simulation de carburant et consommation
  - Gestion thermique du moteur

- **Contrôles de conduite**
  - Accélération progressive
  - Freinage réaliste
  - Direction avec ratio variable
  - Systèmes de suspension

- **Interface utilisateur (HUD)**
  - Affichage vitesse (km/h)
  - Affichage RPM
  - Sélecteur de vitesse
  - Jauge carburant
  - Température moteur

### 🔄 À venir
- Système de caméra interne/externe
- Passagers et system d'embarquement
- Routes et environnement 3D
- Système de trajet/itinéraire
- Sons moteur et effets sonores
- Système de dégâts et usure
- Multiplayer (réseau)

## 📋 Requirements

- **Unreal Engine 5.4** ou supérieur
- **Visual Studio 2022** (ou un IDE C++ compatible)
- **Windows 10/11** ou **Linux** ou **macOS**

## 🚀 Installation

### 1. Cloner le dépôt
```bash
git clone https://github.com/schoolcuplautrec/bus-simulator-3d.git
cd bus-simulator-3d
```

### 2. Générer les fichiers du projet
```bash
# Sur Windows
right-click sur BusSimulator.uproject -> Generate Visual Studio project files

# Ou depuis la ligne de commande
./GenerateProjectFiles.bat
```

### 3. Compiler le projet
```bash
# Ouvrir la solution Visual Studio générée
BusSimulator.sln

# Compiler en mode Development Editor
```

### 4. Lancer le projet
- Double-cliquer sur `BusSimulator.uproject` pour ouvrir dans Unreal Engine

## 📁 Structure du projet

```
bus-simulator-3d/
├── Source/
│   ├── BusSimulator/
│   │   ├── Public/
│   │   │   ├── Vehicles/
│   │   │   │   └── BusVehicle.h
│   │   │   ├── Systems/
│   │   │   │   ├── PhysicsSystem.h
│   │   │   │   └── DriveSystem.h
│   │   │   └── UI/
│   │   │       └── BusHUD.h
│   │   ├── Private/
│   │   │   ├── Vehicles/
│   │   │   │   └── BusVehicle.cpp
│   │   │   ├── Systems/
│   │   │   │   ├── PhysicsSystem.cpp
│   │   │   │   └── DriveSystem.cpp
│   │   │   └── UI/
│   │   │       └── BusHUD.cpp
│   │   └── BusSimulator.Build.cs
│   └── BusSimulator.Target.cs
├── BusSimulator.uproject
├── README.md
└── .gitignore
```

## 🎮 Contrôles (À implémenter)

| Action | Clavier | Manette |
|--------|---------|----------|
| Accélération | W | RT |
| Freinage | S | LT |
| Direction gauche | A | Left Stick ← |
| Direction droite | D | Left Stick → |
| Vitesse supérieure | E | RB |
| Vitesse inférieure | Q | LB |
| Démarrer/Arrêter moteur | I | Y |

## 🔧 Configuration des paramètres

Tous les paramètres peuvent être modifiés dans l'éditeur Unreal :

### Moteur
- `Max Engine Power` : Puissance maximale (Watts)
- `Max RPM` : Tours/minute maximum
- `Engine Inertia` : Inertie du moteur

### Transmission
- `Gear Ratios` : Rapports de chaque vitesse
- `Final Drive Ratio` : Démultiplication finale

### Physique
- `Bus Mass` : Masse du bus (kg)
- `Suspension Stiffness` : Rigidité de la suspension
- `Max Steering Angle` : Angle de braquage maximum

## 📊 Modèles physiques

### Adhérence des pneus (Pacejka)
Modèle simplifié de la courbe d'adhérence avec coefficient de glissement.

### Transmission
Calcul du couple avec prise en compte :
- RPM et courbe de puissance
- Rapport d'engrenage
- Adhérence des roues

### Résistances
- Aérodynamique : `F = 0.5 * ρ * Cd * A * v²`
- Roulement : `F = Crr * m * g`

## 🐛 Debugging

### Affichage des données en temps réel
```cpp
GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Yellow, 
    FString::Printf(TEXT("Speed: %.1f km/h"), Speed));
```

### Vérifier les collisions
Activer la visualisation des collisions dans l'éditeur :
`Show -> Collisions`

## 📚 Ressources

- [Documentation Unreal Engine 5](https://docs.unrealengine.com/)
- [Unreal C++ API Reference](https://docs.unrealengine.com/en-US/API/)
- [Physics Simulation](https://docs.unrealengine.com/en-US/Engine/Physics/)

## 📝 Licence

Ce projet est licencié sous **MIT License**.

## 👤 Auteur

**schoolcuplautrec** - Concepteur du projet

## 🤝 Contribution

Les contributions sont bienvenues ! N'hésitez pas à :
1. Fork le projet
2. Créer une branche feature (`git checkout -b feature/AmazingFeature`)
3. Commit vos changements (`git commit -m 'Add some AmazingFeature'`)
4. Push vers la branche (`git push origin feature/AmazingFeature`)
5. Ouvrir une Pull Request

## ⚠️ Note

Ce projet est en **développement actif**. Certaines fonctionnalités peuvent être incomplètes ou sujettes à des modifications.
