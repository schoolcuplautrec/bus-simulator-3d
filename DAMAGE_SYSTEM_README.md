# Système de Dégâts Réaliste - BeamNG Drive Style

## 🚗💥 Caractéristiques

### **Système de Dégâts Complet**

#### 1️⃣ **Carrosserie (Body Integrity)**
- Santé max: 1000 points
- Endommagée par les collisions
- Affecte la tenue de route
- Déformation visible progressive

#### 2️⃣ **Moteur (Engine Health)**
- Santé max: 500 points
- Perd santé lors d'impacts violents (>5000J)
- Peut s'enflammer si surchauffé
- Destruction = arrêt du véhicule

#### 3️⃣ **Transmission (Transmission Health)**
- Santé max: 400 points
- Endommagée lors d'impacts (>3000J)
- Cassée = perte de puissance
- Impact sur l'accélération

#### 4️⃣ **Suspension (Suspension Health)**
- 4 roues indépendantes
- Santé max: 300 points par roue
- Cassure à compression > 150cm
- Roue endommagée = perte de contrôle

---

## 🎯 Types de Dégâts

### **Impact/Collision**
```
Energy = Force × Distance
Damage = Energy × AngleFactor × 0.01
Multiplier = 1.5x
```

### **Tonneau/Rollover**
```
Damage = |Angle| × 2.0x (DOUBLE MULTIPLIER)
Affecte: Carrosserie, Moteur, Toutes les suspensions
```

### **Suspension Failure**
```
Si Compression > 150cm:
  Damage = (Compression - 150) × 0.5
  Roue endommagée = impossible à utiliser
```

### **Surchauffe Moteur**
```
Si Temp > 150°C:
  Moteur prend feu 🔥
  Perte -10 HP/s
  Destruction progressive
```

---

## 🔧 Système de Déformation

### **Déformation des Panneaux**
- 8 panneaux déformables
- Déformation max: 100cm
- Récupération: 5%/seconde
- Affiche les dégâts en temps réel

### **Vitres Cassées**
- 12 vitres en total
- Peuvent se casser lors d'impacts
- Compteur de vitres cassées
- Affecte l'aérodynamique

### **Portes Endommagées**
- 3 portes (avant, milieu, arrière)
- Santé de 0-100 par porte
- Peuvent se coller/bloquer
- Affecte l'accès passagers

### **Châssis Plié (Frame Bend)**
- Limite: -100 à +100
- >50% = "Severely Bent"
- Compromet la manipulation
- Impossible à réparer en simulation

---

## 📊 Affichage des Dégâts (HUD)

### **Barre de Santé Globale**
- 100-80%: 🟢 Excellent
- 80-60%: 🟡 Good
- 60-40%: 🟠 Damaged
- 40-20%: 🔴 Severely Damaged
- 0-20%: ☠️ Critical

### **Détails par Composant**
- Carrosserie: ░░░░░░░░░░
- Moteur: ░░░░░░░░░░
- Transmission: ░░░░░░░░░░
- Roue 1-4: ░░ ░░ ░░ ░░

### **Alertes**
- ⚠️ Engine Damaged
- ❌ Wheel Destroyed
- 🔥 Fire Alert
- 💥 Severe Collision

---

## 🎮 Implémentation dans le Gameplay

### **Code C++ pour Appliquer des Dégâts**

```cpp
// Collision frontale
DamageSystem->ApplyImpactDamage(
    ImpactPoint,
    ImpactForce,
    5000.0f  // Énergie J
);

// Tonneau complet
DamageSystem->ApplyRolloverDamage(90.0f);  // 90°

// Suspension cassée
DamageSystem->ApplySuspensionDamage(200.0f, 0);  // Roue avant-gauche

// Moteur en feu
DamageSystem->ApplyFireDamage(160.0f);  // °C
```

---

## 📈 Statistiques de Dégâts

| Impact | Énergie | Dégâts Carrosserie | Moteur | Transmission |
|--------|---------|-------------------|--------|---------------|
| Faible collision | 1,000J | 15 | 0 | 0 |
| Collision modérée | 3,000J | 45 | 22 | 13 |
| Accident grave | 5,000J | 75 | 37 | 22 |
| Tonneau 90° | - | 180 | 108 | 72 |
| Crash total | 10,000J | 150 | 75 | 50 |

---

## 🎨 Effets Visuels

### **Déformation Progressive**
- Petits impacts: Légers dégâts visuels
- Impacts moyens: Panneaux visiblement endommagés
- Accidents graves: Carrosserie déformée
- Tonneau: Structure complètement écrasée

### **Effets Sonores**
- Bruit de collision réaliste
- Grincement de métal
- Sonnerie d'alerte moteur
- Crépitement feu 🔥

### **Particules**
- Étincelles lors d'impacts
- Fumée du moteur surchauffé
- Flammes si incendie
- Débris volant

---

## 🔄 Récupération des Dégâts

### **Réparation Limitée**
- Panels: -5%/s (récupération naturelle)
- Moteur: ❌ Non réparable si détruit
- Roues: ❌ Non réparable si cassées
- Châssis: ❌ Jamais réparable

### **Mécanique Réaliste**
- Plus les dégâts sont graves, plus difficile à contrôler
- Roues cassées = impossible d'accélérer
- Moteur détruit = arrêt complet
- Pas de magique"heal"

---

**Profitez d'une expérience de conduite réaliste avec des conséquences physiques!** 💥🚌
